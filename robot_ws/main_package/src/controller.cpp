#include <functional>
#include <memory>

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/int32.hpp"
#include "std_msgs/msg/float32.hpp"
#include "geometry_msgs/msg/twist.hpp"

#include "../include/config.h"

class ControllerNode : public rclcpp::Node {
  public:
    ControllerNode() : Node("controller_node") {
        lidar_subscription_ = this->create_subscription<std_msgs::msg::Float32>(
            "obstacle_distance", 10, std::bind(&ControllerNode::lidarCallback, this, std::placeholders::_1));

        control_subscription_ = this->create_subscription<std_msgs::msg::Int32>(
            "control_command", 10, std::bind(&ControllerNode::controlCallback, this, std::placeholders::_1));

        motor_publisher_ = this->create_publisher<std_msgs::msg::Int32>("motor_commands", 10);
    }

  private:
    rclcpp::Subscription<std_msgs::msg::Float32>::SharedPtr lidar_subscription_;
    rclcpp::Subscription<std_msgs::msg::Int32>::SharedPtr control_subscription_;
    rclcpp::Publisher<std_msgs::msg::Int32>::SharedPtr motor_publisher_;

    float min_obstacle_distance = 1.0;
    bool avoiding_obstacle = false;

    void lidarCallback(const std_msgs::msg::Float32::SharedPtr obstacle_distance) {
      if (obstacle_distance->data <= min_obstacle_distance) {
        avoiding_obstacle = true;

        std_msgs::msg::Int32 motor_command;
        motor_command.data = TURN_RIGHT;

        motor_publisher_->publish(motor_command);
        RCLCPP_INFO(this->get_logger(), "Obstacle detected, avoidance maneuvers.");
      }
      else {
        avoiding_obstacle = false;
      }
    }

    void controlCallback(const std_msgs::msg::Int32::SharedPtr control_command) {
        std_msgs::msg::Int32 motor_command;
        motor_command.data = control_command->data;

        if (avoiding_obstacle == false) {
          motor_publisher_->publish(motor_command);
        }
    }
};

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<ControllerNode>());
  rclcpp::shutdown();
  return 0;
}