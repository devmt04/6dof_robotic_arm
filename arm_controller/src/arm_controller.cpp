#include "arm_controller/arm_controller.hpp"

ArmController::ArmController( const rclcpp::Node::SharedPtr &node, const std::string &planning_group) 
    : node_(node), move_group_(node, planning_group), has_plan_(false){}

geometry_msgs::msg::Pose ArmController::getCurrentPose() const
{
    return move_group_.getCurrentPose().pose;
}

std::vector<double> ArmController::getCurrentJointValues() const
{
    return move_group_.getCurrentJointValues();
}

bool ArmController::moveToPose(
    const geometry_msgs::msg::Pose &pose)
{
    move_group_.setPoseTarget(pose);

    return plan();
}

bool ArmController::moveToJointState(
    const std::vector<double> &joints)
{
    move_group_.setJointValueTarget(joints);

    return plan();
}

bool ArmController::moveToNamedTarget(
    const std::string &name)
{
    move_group_.setNamedTarget(name);

    return plan();
}

bool ArmController::plan()
{
    auto result = move_group_.plan(current_plan_);

    has_plan_ =
        (result == moveit::core::MoveItErrorCode::SUCCESS);

    return has_plan_;
}

bool ArmController::execute()
{
    if (!has_plan_)
    {
        RCLCPP_WARN(
            node_->get_logger(),
            "No valid plan available.");

        return false;
    }

    auto result = move_group_.execute(current_plan_);

    return result == moveit::core::MoveItErrorCode::SUCCESS;
}

void ArmController::stop()
{
    move_group_.stop();
}

void ArmController::setVelocityScaling(double scale)
{
    move_group_.setMaxVelocityScalingFactor(scale);
}

void ArmController::setAccelerationScaling(double scale)
{
    move_group_.setMaxAccelerationScalingFactor(scale);
}

void ArmController::setPlanningTime(double time)
{
    move_group_.setPlanningTime(time);
}