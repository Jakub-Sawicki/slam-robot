#include <functional>
#include <memory>
#include <string>

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/int32.hpp"

#include "../include/config.h"

using namespace std::chrono_literals;

class SimControlsDriverNode : public rclcpp::Node {
  public:
    SimControlsDriverNode() : Node("sim_controls_driver_node")
    {
        subscription_ = this->create_subscription<std_msgs::msg::Int32>(
            "keyboard/keypress", 1, std::bind(&SimControlsDriverNode::callbackFunction, this, std::placeholders::_1));

        publisher_ = this->create_publisher<std_msgs::msg::Int32>("control_command", 1);
    }

  private:
    rclcpp::Subscription<std_msgs::msg::Int32>::SharedPtr subscription_;
    rclcpp::Publisher<std_msgs::msg::Int32>::SharedPtr publisher_;

    void callbackFunction(const std_msgs::msg::Int32::SharedPtr keyboard_msg) {
        
        RCLCPP_INFO(this->get_logger(), "Key id: '%i'", keyboard_msg->data);

        std_msgs::msg::Int32 output_msg;

        switch (keyboard_msg->data) {
          case 16777235:  // forward key
            output_msg.data = MOVE_FORWARD;
            RCLCPP_INFO(this->get_logger(), "Forward key");
            break;
          case 16777237:  // reverse key
            output_msg.data = MOVE_BACKWARS;
            RCLCPP_INFO(this->get_logger(), "Reverse key");
            break;
          case 16777236:  // right key
            output_msg.data = TURN_RIGHT;
            RCLCPP_INFO(this->get_logger(), "Right key");
            break;
          case 16777234:  // left left
            output_msg.data = TURN_LEFT;
            RCLCPP_INFO(this->get_logger(), "Left key");
            break;
          default:  // other key
            RCLCPP_INFO(this->get_logger(), "Key not recognized");
            break;
        }

        publisher_->publish(output_msg);
    }
};

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<SimControlsDriverNode>());
  rclcpp::shutdown();
  return 0;
}