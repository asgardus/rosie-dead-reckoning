
#include <ros/ros.h>
#include <std_msgs/Float32.h>
#include <phidgets/motor_encoder.h>
#include <geometry_msgs/Twist.h>

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

int main(int argc, char **argv){
    ros::init(argc, argv, "rosie_dead_reckon");

    ros::NodeHandle n;
    ros::Subscriber encoderLeft_sub = n.subscribe("/motorLeft/encoder", 1, encoderLeftCallback);
    ros::Subscriber encoderRight_sub = n.subscribe("/motorRight/encoder", 1, encoderRightCallback);


    ros::Rate loop_rate(10);

while(ros::ok())
{
    ros::spinOnce();
    loop_rate.sleep();
}

}
