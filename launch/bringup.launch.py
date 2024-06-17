from launch import LaunchDescription
from launch_ros.actions import Node
from launch.actions import IncludeLaunchDescription
from launch.launch_description_sources import PythonLaunchDescriptionSource
from ament_index_python.packages import get_package_share_directory
import os

def generate_launch_description():
    gazebo_launch = IncludeLaunchDescription(
        PythonLaunchDescriptionSource([os.path.join(
            get_package_share_directory('gazebo_ros'), 'launch', 'gazebo.launch.py')])
    )

    robot_state_publisher = Node(
        package='robot_state_publisher',
        executable='robot_state_publisher',
        name='robot_state_publisher',
        output='screen',
        parameters=[{'robot_description': os.path.join(
            get_package_share_directory('my_robot_description'), 'urdf', 'robot_description.urdf')}]
    )

    slam_node = Node(
        package='my_robot',
        executable='slam_node',
        name='slam_node',
        output='screen'
    )

    nav_node = Node(
        package='my_robot',
        executable='nav_node',
        name='nav_node',
        output='screen'
    )

    return LaunchDescription([
        gazebo_launch,
        robot_state_publisher,
        slam_node,
        nav_node,
    ])