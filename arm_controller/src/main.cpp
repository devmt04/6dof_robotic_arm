#include <thread>

#include <rclcpp/rclcpp.hpp>

#include "arm_controller/arm_controller.hpp"

int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);

    rclcpp::NodeOptions options;

    options.automatically_declare_parameters_from_overrides(
        true);

    auto node =
        std::make_shared<rclcpp::Node>(
            "arm_controller_node",
            options);

    rclcpp::executors::SingleThreadedExecutor executor;

    executor.add_node(node);

    std::thread([&executor]()
    {
        executor.spin();
    }).detach();

    ArmController arm(node, "arm");

    arm.setPlanningTime(5.0);

    arm.setVelocityScaling(0.3);

    arm.setAccelerationScaling(0.3);

    geometry_msgs::msg::Pose pose;

    pose.orientation.w = 1.0;

    pose.position.x = 0.30;
    pose.position.y = 0.15;
    pose.position.z = 0.40;

    if (arm.moveToPose(pose))
    {
        RCLCPP_INFO(
            node->get_logger(),
            "Planning successful.");

        arm.execute();
    }
    else
    {
        RCLCPP_ERROR(
            node->get_logger(),
            "Planning failed.");
    }

    rclcpp::shutdown();

    return 0;
}