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

#ifndef PPO_ROS__VISIBILITY_CONTROL_H_
#define PPO_ROS__VISIBILITY_CONTROL_H_

// This logic was borrowed (then namespaced) from the examples on the gcc wiki:
//     https://gcc.gnu.org/wiki/Visibility

#if defined _WIN32 || defined __CYGWIN__
#ifdef __GNUC__
#define PPO_ROS_EXPORT __attribute__((dllexport))
#define PPO_ROS_IMPORT __attribute__((dllimport))
#else
#define PPO_ROS_EXPORT __declspec(dllexport)
#define PPO_ROS_IMPORT __declspec(dllimport)
#endif
#ifdef PPO_ROS_BUILDING_LIBRARY
#define PPO_ROS_PUBLIC PPO_ROS_EXPORT
#else
#define PPO_ROS_PUBLIC PPO_ROS_IMPORT
#endif
#define PPO_ROS_PUBLIC_TYPE PPO_ROS_PUBLIC
#define PPO_ROS_LOCAL
#else
#define PPO_ROS_EXPORT __attribute__((visibility("default")))
#define PPO_ROS_IMPORT
#if __GNUC__ >= 4
#define PPO_ROS_PUBLIC __attribute__((visibility("default")))
#define PPO_ROS_LOCAL __attribute__((visibility("hidden")))
#else
#define PPO_ROS_PUBLIC
#define PPO_ROS_LOCAL
#endif
#define PPO_ROS_PUBLIC_TYPE
#endif

#endif  // PPO_ROS__VISIBILITY_CONTROL_H_
