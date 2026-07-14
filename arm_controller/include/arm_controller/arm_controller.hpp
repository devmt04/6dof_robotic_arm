#pragma once

#include <memory>
#include <string>
#include <vector>

#include <rclcpp/rclcpp.hpp>

#include <geometry_msgs/msg/pose.hpp>

#include <moveit/move_group_interface/move_group_interface.hpp>

class ArmController
{
public:
    explicit ArmController(
        const rclcpp::Node::SharedPtr &node,
        const std::string &planning_group);

    geometry_msgs::msg::Pose getCurrentPose() const;

    std::vector<double> getCurrentJointValues() const;

    bool moveToPose(const geometry_msgs::msg::Pose &pose);

    bool moveToJointState(const std::vector<double> &joints);

    bool moveToNamedTarget(const std::string &name);

    bool plan();

    bool execute();

    void stop();

    void setVelocityScaling(double scale);

    void setAccelerationScaling(double scale);

    void setPlanningTime(double time);

private:
    rclcpp::Node::SharedPtr node_;

    moveit::planning_interface::MoveGroupInterface move_group_;

    moveit::planning_interface::MoveGroupInterface::Plan current_plan_;

    bool has_plan_;
};