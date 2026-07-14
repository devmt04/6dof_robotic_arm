ros2 pkg create arm_controller \
    --build-type ament_cmake \
    --license Apache-2.0 \
    --dependencies \
        rclcpp \
        moveit_ros_planning_interface \
        geometry_msgs \
        sensor_msgs \
        tf2_geometry_msgs



Dependencies explained
rclcpp: ROS 2 C++ client library.
moveit_ros_planning_interface: Provides MoveGroupInterface, which is your primary API for planning and execution.
geometry_msgs: For pose goals (geometry_msgs::msg::Pose).
sensor_msgs: Useful for joint states and other sensor messages.
tf2_geometry_msgs: For converting between TF2 types and geometry messages.

As your project grows, you'll likely add dependencies such as:

moveit_msgs
shape_msgs
visualization_msgs
tf2_ros
Eigen3


colcon build --cmake-args -DCMAKE_EXPORT_COMPILE_COMMANDS=ON --packages-select arm_controller