cmake_minimum_required(VERSION 3.8)
project(ppo_ros)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

find_package(ament_cmake_auto REQUIRED)
ament_auto_find_build_dependencies()

generate_parameter_library(
  ${PROJECT_NAME}_parameters # cmake target name for the parameter library
  params/${PROJECT_NAME}_parameters.yaml # path to input yaml file
)

ament_auto_add_library(${PROJECT_NAME} SHARED
  src/${PROJECT_NAME}_component.cpp
)
target_link_libraries(${PROJECT_NAME}
  ${PROJECT_NAME}_parameters
)
rclcpp_components_register_nodes(${PROJECT_NAME} "ppo_ros::PPOComponent")

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  ament_lint_auto_find_test_dependencies()
endif()

install(DIRECTORY
  models
  params
  launch
  DESTINATION share/${PROJECT_NAME}/
)

ament_auto_package()
