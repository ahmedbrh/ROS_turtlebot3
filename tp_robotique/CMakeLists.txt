# %Tag(FULLTEXT)%
cmake_minimum_required(VERSION 2.8.3)
project(tp_robotique)

## Find catkin and any catkin packages
find_package(catkin REQUIRED COMPONENTS roscpp rospy std_msgs genmsg)

## Declare a catkin package
catkin_package(
)

include_directories(${catkin_INCLUDE_DIRS})

add_executable(tp1_node src/tp1.cpp) 
target_link_libraries(tp1_node ${catkin_LIBRARIES})
add_executable(lidar_node src/detection_obstacles.cpp) 
target_link_libraries(lidar_node ${catkin_LIBRARIES})
# %EndTag(FULLTEXT)%