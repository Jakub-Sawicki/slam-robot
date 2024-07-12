#!/bin/bash

# Source the ROS 2 setup file
source /opt/ros/jazzy/setup.bash
source ../robot_ws/install/setup.bash

# launch gazebo and simulation nodes from launch file 
ros2 launch main_package simulation_launch.py


