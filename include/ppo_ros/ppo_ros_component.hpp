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

#include <torch/script.h>

#include <ament_index_cpp/get_package_share_directory.hpp>
#include <ppo_ros/ppo_ros_parameters.hpp>
#include <ppo_ros/visibility_control.hpp>
#include <rclcpp/rclcpp.hpp>
#include <rclcpp_components/register_node_macro.hpp>
#include <torch_msgs/msg/fp32_tensor.hpp>
#include <torch_util/type_adapter.hpp>

namespace ppo_ros
{

using AdaptedType = rclcpp::TypeAdapter<torch::Tensor, torch_msgs::msg::FP32Tensor>;

class PPOComponent : public rclcpp::Node
{
public:
  PPO_ROS_PUBLIC
  explicit PPOComponent(const rclcpp::NodeOptions & options);

  ~PPOComponent() override {}

private:
  std::shared_ptr<rclcpp::Subscription<AdaptedType>> observation_subscriber_;
  std::shared_ptr<rclcpp::Publisher<AdaptedType>> action_publisher_;
  const ppo_ros::Params parameters_;
  torch::jit::script::Module actor;
};
}  // namespace ppo_ros
