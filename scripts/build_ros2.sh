#!/bin/bash

# Navigate to the ROS2 workspace
cd ~/my_robotics_project/ros2_ws

# Build the workspace
colcon build --symlink-install

# Source the setup file
source install/setup.bash

echo "ROS2 workspace built and sourced."