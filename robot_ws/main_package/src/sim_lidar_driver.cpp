#include <functional>
#include <memory>
#include <string>

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/float32.hpp"
#include "sensor_msgs/msg/laser_scan.hpp"

class SimLidarDriverNode : public rclcpp::Node {
  public:
    SimLidarDriverNode() : Node("sim_lidar_driver_node")
    {
        subscription_ = this->create_subscription<sensor_msgs::msg::LaserScan>(
            "lidar", 10, std::bind(&SimLidarDriverNode::callbackFunction, this, std::placeholders::_1));

        publisher_ = this->create_publisher<std_msgs::msg::Float32>("obstacle_distance", 10);
    }

  private:
    rclcpp::Subscription<sensor_msgs::msg::LaserScan>::SharedPtr subscription_;
    rclcpp::Publisher<std_msgs::msg::Float32>::SharedPtr publisher_;

    void callbackFunction(const sensor_msgs::msg::LaserScan::SharedPtr lidar_msg) {

        std_msgs::msg::Float32 obstacle_distance;

        obstacle_distance.data = lidar_msg->range_max;

        for (auto & range : lidar_msg->ranges) {
            if ((range > lidar_msg->range_min || range < lidar_msg->range_max) && range < obstacle_distance.data ) {
                obstacle_distance.data = range;
            }
        }

        publisher_->publish(obstacle_distance);
    }
};

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<SimLidarDriverNode>());
  rclcpp::shutdown();
  return 0;
}