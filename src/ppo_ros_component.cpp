// Copyright 2024 Team Re-Boot. All rights reserved.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include <ppo_ros/ppo_ros_component.hpp>

namespace ppo_ros
{
PPOComponent::PPOComponent(const rclcpp::NodeOptions & options)
: Node("ppo_component", options),
  parameters_(ppo_ros::ParamListener(get_node_parameters_interface()).get_params())
{
  actor = torch::jit::load(
    ament_index_cpp::get_package_share_directory(parameters_.model_package) + "/" +
    parameters_.model);
  // Create a subscription to the adapted type
  subscriber_ =
    this->create_subscription<AdaptedType>("observation", 1, [this](const torch::Tensor & msg) {
      /// @sa https://github.com/leggedrobotics/rsl_rl/blob/d38a378b13a60ea570923754184f84f48979ad74/rsl_rl/modules/actor_critic.py#L109C9-L109C13
      const auto mean = actor.forward({msg}).toTensor();
      /// @sa https://github.com/leggedrobotics/rsl_rl/blob/d38a378b13a60ea570923754184f84f48979ad74/rsl_rl/modules/actor_critic.py#L111-L112
      const auto std = torch::tensor(parameters_.std, torch::TensorOptions().dtype(torch::kFloat32))
                         .expand({mean.size(0), mean.size(1)});

      const auto sample = [](const double mean_val, const double stddev_val) {
        auto rand1 = torch::rand({1});
        auto rand2 = torch::rand({1});
        double z0 = std::sqrt(-2.0 * std::log(rand1.item<double>())) *
                    std::cos(2.0 * M_PI * rand2.item<double>());
        return mean_val + stddev_val * z0;
      };

      auto mean_accessor = mean.accessor<float, 2>();
      auto std_accessor = std.accessor<float, 2>();
      for (int i = 0; i < mean_accessor.size(0); ++i) {
        for (int j = 0; j < mean_accessor.size(1); ++j) {
          sample(mean_accessor[i][j], std_accessor[i][j]);
        }
      }
    });
}
}  // namespace ppo_ros
