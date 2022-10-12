#include <ros/ros.h>
#include <nav_msgs/Odometry.h>
#include <geometry_msgs/Twist.h>
#include <geometry_msgs/PoseStamped.h>
#include <tf/tf.h>
#include <std_msgs/Float32.h>
int i = 0 ;
double dist = 0;

//Initial position
double poseX = 0 ;
double poseY = 0 ;
double poseZ = 0 ;

// initial angle (initial yaw)
double firstYaw;

// To have the current yaw
double roll, pitch, yaw;

// To should publish and subscribe on the new topics
int avancer=0,tourner=0;

// coordonnées polaires
double orient = 0, distRToObst=0;
// Odom callback
void callback(const nav_msgs::Odometry &msg){
    // q1: Have the initial position and the others
    i++;

    // To get the initial position and intial yaw 
    tf::Quaternion q(
        msg.pose.pose.orientation.x,
        msg.pose.pose.orientation.y,
        msg.pose.pose.orientation.z, 
        msg.pose.pose.orientation.w      
    );

    tf::Matrix3x3 m(q);
    
    if(i == 1){
        poseX = msg.pose.pose.position.x;
        poseY = msg.pose.pose.position.y;
        poseZ = msg.pose.pose.position.z;
        m.getRPY(roll,pitch, firstYaw);
    }

    // Distance euclidienne entre la position courante et la position initial 
    dist = pow(pow(msg.pose.pose.position.x-poseX,2) + pow(msg.pose.pose.position.y-poseY,2) + pow(msg.pose.pose.position.z-poseZ,2) , 0.5) ;
    
    //Affiche 
    ROS_INFO_STREAM(i<<" Autre :\n"<<msg.pose.pose.position.x<<" "<<msg.pose.pose.position.y<<" "<<msg.pose.pose.position.z);
    ROS_INFO_STREAM(i<<" La distance euclidienne est :\n"<<dist);
    m.getRPY(roll, pitch, yaw);
    ROS_INFO_STREAM(i<<" Orientation :\n"<<firstYaw<<" "<<yaw);
}
// callback topic avancer 
void callback_avancer(const std_msgs::Float32 &msg){
    avancer = msg.data;
    ROS_INFO_STREAM("Avancer :\n"<<avancer);
}
// callback topic tourner 
void callback_tourner(const std_msgs::Float32 &msg){
    tourner = msg.data;
    ROS_INFO_STREAM("Tourner :\n"<<tourner);
}

// Callback goal
void callback_goal(const geometry_msgs::PoseStamped &msg){
   // desired destinations
   ROS_INFO_STREAM(i<<" Destination :\n"<<msg.pose.position.x<<msg.pose.position.y<<msg.pose.position.z);

   // Obstacle positions
   geometry_msgs::PoseStamped obsPose;
   // coordonées polaires
   //distRToObst = pow(pow(msg.pose.position.x-obsPose.pose.position.x,2) + pow(msg.pose.position.y-obsPose.pose.position.y,2) , 0.5) ;
   //orient = 2*atan(((msg.pose.orientation.y-obsPose.pose.orientation.y)/(msg.pose.orientation.x-obsPose.pose.orientation.x))/(1+(msg.pose.orientation.x-obsPose.pose.orientation.x))/distRToObst) ;
}

int main(int argc, char ** argv){
    ros::init(argc, argv, "tp1");

    ros::NodeHandle nh;

    //  Publisher cmd_vel
    ros::Publisher pub = nh.advertise<geometry_msgs::Twist>("/cmd_vel", 1000);

    //Publisher Move goal 
    ros::Publisher pub_goal = nh.advertise<geometry_msgs::PoseStamped>("/move_base_simple/goal", 1000);
      
    // Subscriber avancer&tourner 
    ros::Subscriber sub_avancer = nh.subscribe("/avancer", 1000, &callback_avancer);
    ros::Subscriber sub_tourner = nh.subscribe("/tourner", 1000, &callback_tourner);
    
    // Subscriber odom 
    ros::Subscriber sub = nh.subscribe("/odom", 1000, &callback);

    ros::Rate loop_rate(10);
    
    while(ros::ok()){

        // cmd_vel  message 
        geometry_msgs::Twist msg;
        
        
        // Condidition for "avancer & tourner"
        int angle = tourner ; 
        double angleParcouru;
        if(dist>=avancer){
            msg.linear.x = 0;
            if(yaw >firstYaw){
                angleParcouru = yaw - firstYaw ;
            }else {
                angleParcouru = 2*M_PI + yaw + firstYaw ;
            }
            
            if(((angleParcouru*180)/M_PI)>=angle){
                msg.angular.z = 0 ;
            }else if(tourner>0){
                msg.angular.z = 0.6 ;
                msg.angular.x=msg.angular.y=0;
            }
        }
        else if(avancer>0)
            msg.linear.x = 0.1;
            msg.linear.y=msg.linear.z=0;
        

        // Publish in the cmd_vel 
        pub.publish(msg);
       
        ros::spinOnce();

        loop_rate.sleep();
    }
}