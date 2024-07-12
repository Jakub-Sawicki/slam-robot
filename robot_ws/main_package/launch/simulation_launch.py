from launch import LaunchDescription
from launch_ros.actions import Node
from launch.actions import ExecuteProcess

def generate_launch_description():
    return LaunchDescription([
        Node(
            package='ros_gz_bridge',
            executable='parameter_bridge',
            name='parameter_bridge',
            output='screen',
            parameters=[{'config_file': '/home/kuba/Documents/slam-robot/scripts/ros_gz_bridge.yaml'}]
        ),
        Node(
            package='main_package',
            executable='controller_node',
            name='controller_node',
            output='screen'
        ),
        Node(
            package='main_package',
            executable='sim_lidar_driver_node',
            name='sim_lidar_driver_node',
            output='screen'
        ),
        Node(
            package='main_package',
            executable='sim_motor_driver',
            name='sim_motor_driver',
            output='screen'
        ),
        Node(
            package='main_package',
            executable='sim_controls_driver_node',
            name='sim_controls_driver_node',
            output='screen'
        ),
    
        ExecuteProcess(
            cmd=['gz', 'sim', '../config/robot_description/robot_model.sdf'],
            output='screen'
        )
    ])
