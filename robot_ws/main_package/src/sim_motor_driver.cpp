#include <functional>
#include <memory>
#include <string>

#include "rclcpp/rclcpp.hpp"
#include "geometry_msgs/msg/twist.hpp"
#include "std_msgs/msg/int32.hpp"

#include "../include/config.h"

class SimMotorDriver : public rclcpp::Node {
  public:
    SimMotorDriver() : Node("sim_motor_driver")
    {
      subscription_ = this->create_subscription<std_msgs::msg::Int32>(
            "motor_commands", 10, std::bind(&SimMotorDriver::callbackFunction, this, std::placeholders::_1));

      publisher_ = this->create_publisher<geometry_msgs::msg::Twist>("cmd_vel", 10);
    }

  private:
    rclcpp::Subscription<std_msgs::msg::Int32>::SharedPtr subscription_;
    rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr publisher_;

    geometry_msgs::msg::Twist assignTwist(float linear, float angular) {
      geometry_msgs::msg::Twist output_msg;

      output_msg.linear.x = linear;
      output_msg.linear.y = 0;
      output_msg.linear.z = 0;

      output_msg.angular.x = 0;
      output_msg.angular.y = 0;
      output_msg.angular.z = angular;

      return output_msg;
    }

    void callbackFunction(const std_msgs::msg::Int32::SharedPtr motor_commands) {
        geometry_msgs::msg::Twist output_msg;

        float linear_speed = 1;
        float rotational_speed = 0.4;

        switch (motor_commands->data) {
          case MOVE_FORWARD:
            output_msg = SimMotorDriver::assignTwist(linear_speed, 0);
            break;
          case MOVE_BACKWARS:
            output_msg = SimMotorDriver::assignTwist(-1 * linear_speed, 0);
            break;
          case TURN_RIGHT:
            output_msg = SimMotorDriver::assignTwist(0, -1 * rotational_speed);
            break;
          case TURN_LEFT:
            output_msg = SimMotorDriver::assignTwist(0, rotational_speed);
            break;
          default:
            RCLCPP_INFO(this->get_logger(), "Wrong motor command.");
            break;
        }

        publisher_->publish(output_msg);
    }
};

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<SimMotorDriver>());
  rclcpp::shutdown();
  return 0;
}