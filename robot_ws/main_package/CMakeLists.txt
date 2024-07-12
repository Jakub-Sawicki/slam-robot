cmake_minimum_required(VERSION 3.8)
project(main_package)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)
find_package(sensor_msgs REQUIRED)

#find_package(gz-transport13 QUIET REQUIRED OPTIONAL_COMPONENTS log)
#set(GZ_TRANSPORT_VER ${gz-transport13_VERSION_MAJOR})

include_directories(${CMAKE_BINARY_DIR})

add_executable(controller_node src/controller.cpp)
add_executable(sim_lidar_driver_node src/sim_lidar_driver.cpp)
add_executable(sim_motor_driver src/sim_motor_driver.cpp)
add_executable(sim_controls_driver_node src/sim_robot_controls.cpp)

# Specify libraries to link
ament_target_dependencies(controller_node rclcpp std_msgs sensor_msgs)
ament_target_dependencies(sim_lidar_driver_node rclcpp std_msgs sensor_msgs)
ament_target_dependencies(sim_motor_driver rclcpp std_msgs geometry_msgs)
ament_target_dependencies(sim_controls_driver_node rclcpp std_msgs)

# Install the target
install(TARGETS
  controller_node
  sim_lidar_driver_node
  sim_motor_driver
  sim_controls_driver_node
  DESTINATION lib/${PROJECT_NAME})

# Install launch files
install(
  DIRECTORY launch
  DESTINATION share/${PROJECT_NAME}/
)

ament_package()
