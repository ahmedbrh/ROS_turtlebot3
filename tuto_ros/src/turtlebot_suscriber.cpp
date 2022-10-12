#include <ros/ros.h>
#include <std_msgs/String.h>

void callback(const std_msgs::String& msg){
    ROS_INFO_STREAM("J'entends:"<<msg.data<<" ");
}
int main(int argc, char ** argv){
    ros::init(argc, argv, "tuto_ros_sub");

    ros::NodeHandle nh;

    ros::Subscriber sub = nh.subscribe("/commande", 1000, &callback);

    ros::Rate loop_rate(10);

    while(ros::ok()){
        ros::spinOnce();

        loop_rate.sleep();
    }
}