
#include <ros/ros.h>
#include <std_msgs/Float32.h>
#include <phidgets/motor_encoder.h>
#include <geometry_msgs/Pose.h>
#include "phidgets_imu/imu_ros_i.h"
#include <sensor_msgs/Imu.h>
//read from encoder
//read from phidget IMU
//publish pose

double wheelSeparation = 1.0;
double est_w_left = 0.0;
double est_w_right = 0.0;


void encoderLeftCallback(const phidgets::motor_encoder& msg)
{
    ROS_INFO("-----------");
    ROS_INFO("LEFT:: E1: %d, E2: %d", msg.count,msg.count_change);

    est_w_left = ((double)msg.count_change * 10.0 * 2.0 * 3.1415)/(360.0);
}

void encoderRightCallback(const phidgets::motor_encoder& msg)
{
    ROS_INFO("-----------");
    ROS_INFO("RIGHT:: E1: %d, E2: %d", msg.count,msg.count_change);

    est_w_right = ((double)msg.count_change * 10.0 * 2.0 * 3.1415)/(360.0);
}

void rawImuCallBack(const sensor_msgs::Imu::ConstPtr& values)
{
    ROS_INFO("-----------");
    ROS_INFO("linear_acceleration.x: %f, angular_velocity.x: %f", values->linear_acceleration.x, values->angular_velocity.x);

}


int main(int argc, char **argv){
    ros::init(argc, argv, "rosie_dead_reckon");

    ros::NodeHandle n;
    //Subscriptions
    ros::Subscriber encoderLeft_sub = n.subscribe("/motorLeft/encoder", 1, encoderLeftCallback);
    ros::Subscriber encoderRight_sub = n.subscribe("/motorRight/encoder", 1, encoderRightCallback);
    ros::Subscriber phidgetCallback = n.subscribe("/imu/data_raw", 1, rawImuCallBack);
    //publications
    ros::Publisher pose_pub = n.advertise<geometry_msgs::Pose>("/Robot/pose",1);

    ros::Rate loop_rate(10);

    geometry_msgs::Pose pose;

while(ros::ok())
{
    pose.position.x = 1.0;
    pose.position.y = 2.0;
    pose.position.z = 3.0;
    pose.orientation.x = 1.0;
    pose.orientation.y = 2.0;
    pose.orientation.z = 3.0;
    pose.orientation.w = 4.0;
    pose_pub.publish(pose);
    ros::spinOnce();
    loop_rate.sleep();
}

}
