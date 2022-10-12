# %Tag(FULLTEXT)%
cmake_minimum_required(VERSION 2.8.3)
project(tuto_ros)

## Find catkin and any catkin packages
find_package(catkin REQUIRED COMPONENTS roscpp rospy std_msgs genmsg)

## Declare a catkin package
catkin_package(
)

include_directories(${catkin_INCLUDE_DIRS})

add_executable(tuto_ros_pub_node src/turtlebot_publisher.cpp) 
add_executable(tuto_ros_sub_node src/turtlebot_suscriber.cpp) 
target_link_libraries(tuto_ros_pub_node ${catkin_LIBRARIES})
target_link_libraries(tuto_ros_sub_node ${catkin_LIBRARIES})
# %EndTag(FULLTEXT)%