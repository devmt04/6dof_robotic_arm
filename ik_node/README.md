ros2 pkg create \
 --build-type ament_cmake \
 --dependencies moveit_ros_planning_interface rclcpp \
 --node-name hello_moveit hello_moveit


As our robotic arm doesn't carry a spherical wrist, we will not be using any Analytical IK approach, instead we will be using methods like BioIK, those works on feedback/optimization algorithms. 



