#include <ros/ros.h>
#include <std_msgs/String.h>

int main(int argc, char ** argv){
    ros::init(argc, argv, "tuto_ros_pub");

    ros::NodeHandle nh;

    ros::Publisher pub = nh.advertise<std_msgs::String>("/commande", 1000);

    ros::Rate loop_rate(10);
    int count = 0;
    while(ros::ok()){

        std_msgs::String msg;   

        msg.data = "Coucou";

        ROS_INFO("%s", msg.data.c_str());

        pub.publish(msg);

        ros::spinOnce();

        loop_rate.sleep();
    }
}