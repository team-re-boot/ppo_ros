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
  RCLCPP_INFO_STREAM(
    get_logger(), "Loading model from "
                    << ament_index_cpp::get_package_share_directory(parameters_.model_package) +
                         "/" + parameters_.model);
  if (torch::cuda::is_available()) {
    RCLCPP_INFO_STREAM(get_logger(), "CUDA is available");
  } else {
    RCLCPP_INFO_STREAM(get_logger(), "CUDA is not available");
  }
  RCLCPP_INFO_STREAM(get_logger(), "Using device: " << (parameters_.use_cuda ? "CUDA" : "CPU"));
  actor = torch::jit::load(
    ament_index_cpp::get_package_share_directory(parameters_.model_package) + "/" +
    parameters_.model);
  if (parameters_.use_cuda) {
    actor.to(torch::kCUDA);
  } else {
    actor.to(torch::kCPU);
  }
  action_publisher_ = this->create_publisher<AdaptedType>("action", 1);
  observation_subscriber_ =
    this->create_subscription<AdaptedType>("observation", 1, [this](const torch::Tensor & msg) {
      action_publisher_->publish(actor.forward({msg}).toTensor());
    });
}
}  // namespace ppo_ros

#include <rclcpp_components/register_node_macro.hpp>
RCLCPP_COMPONENTS_REGISTER_NODE(ppo_ros::PPOComponent)
