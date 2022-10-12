#include <ros/ros.h>
#include <std_msgs/String.h>
#include <sensor_msgs/LaserScan.h>
#include <std_msgs/String.h>

int inf = 0;
double champDeVision[30] ;
void scanCb(const sensor_msgs::LaserScan &msg){
    for (size_t i = 0; i < msg.ranges.size(); i++)
    {
        if(msg.ranges[i]<0.2)
            inf = 1;
        else
            inf = 0 ;
            
    }
  
 ROS_INFO_STREAM("J'entends:"<<msg.ranges[0]<<" ");
}
void avertirCb(const std_msgs::String &msg){
    ROS_INFO_STREAM(""<<msg.data<<" ");
}
int main(int argc, char ** argv){
    ros::init(argc, argv, "Lidar_Robotique");

    ros::NodeHandle nh;
    ros::Publisher pub_ad = nh.advertise<std_msgs::String>("/Avertir", 1000);
    ros::Subscriber sub_ad = nh.subscribe("/Avertir", 1000, &avertirCb);
    ros::Publisher pub = nh.advertise<sensor_msgs::LaserScan>("/scan", 1000);;
    ros::Subscriber sub = nh.subscribe("/scan", 1000, &scanCb);
    ros::Rate loop_rate(10);
    int count = 0;
    while(ros::ok()){
        std_msgs::String msg;
        
        if(inf == 1){
          
            msg.data = "Robot trop pres d'un obstacle" ;
            ROS_INFO("%s", msg.data.c_str());
            pub_ad.publish(msg);
        
        }


        // detection d'un obstacle 
        sensor_msgs::LaserScan msg2;
        msg2.angle_max = M_PI/12;
        msg2.angle_min = -M_PI/12;
        pub.publish(msg2);

        ros::spinOnce();

        loop_rate.sleep();
    }
}