#include <iostream>
#include <ros/ros.h>
#include <rosbag/bag.h>
#include <cv_bridge/cv_bridge.h>
#include <sensor_msgs/Imu.h>
#include <sensor_msgs/Image.h>
#include <sensor_msgs/MagneticField.h>
using namespace std;

ros::Subscriber imu_sub;
ros::Subscriber image0_sub;
ros::Subscriber image1_sub;
ros::Subscriber mag_sub;

ros::Publisher imu_pub;
ros::Publisher image0_pub;
ros::Publisher image1_pub; 
rosbag::Bag bag;

void imuCallback(const sensor_msgs::ImuPtr &msg);
void image0Callback(const sensor_msgs::ImagePtr &msg);
void image1Callback(const sensor_msgs::ImagePtr &msg);
void magCallback(const sensor_msgs::MagneticFieldConstPtr &msg);

int main(int argc, char **argv)
{
  ros::init(argc, argv, "data_collector_node");
  ros::NodeHandle nh("~");

        imu_sub=nh.subscribe("/imu/data",100,imuCallback);
        image0_sub=nh.subscribe("/mynteye/left/image_raw",10,image0Callback);
        image1_sub=nh.subscribe("/mynteye/right/image_raw",10,image1Callback);
        mag_sub=nh.subscribe("/imu/mag",100,magCallback);

        // imu_pub=nh.advertise<sensor_msgs::Imu>("imu_out",10);
        // image0_pub=nh.advertise<sensor_msgs::Image>("image0_out",10);
        // image1_pub=nh.advertise<sensor_msgs::Image>("image1_out",10);

    bag.open("/home/zhouyuxuan/tes3.bag", rosbag::bagmode::Write);


    ros::spin();

    return 0;
}

void imuCallback(const sensor_msgs::ImuPtr &msg)
{
    auto msg_copy=*msg;
    msg_copy.header.stamp=ros::Time::now();
    bag.write("/imu/data", msg_copy.header.stamp, msg_copy);
    // imu_pub.publish(msg_copy);
}
void image0Callback(const sensor_msgs::ImagePtr &msg)
{
    auto msg_copy=*msg;
    msg_copy.header.stamp=ros::Time::now();
        bag.write("/mynteye/left/image_raw", msg_copy.header.stamp, msg_copy);

    ROS_INFO("image0_time:%f",msg_copy.header.stamp.toSec());
    //image0_pub.publish(msg_copy);
}
void image1Callback(const sensor_msgs::ImagePtr &msg)
{
    auto msg_copy=*msg;
    msg_copy.header.stamp=ros::Time::now();
        bag.write("/mynteye/right/image_raw", msg_copy.header.stamp, msg_copy);

    ROS_INFO("image1_time:%f",msg_copy.header.stamp.toSec());

    //image1_pub.publish(msg_copy);
}

void magCallback(const sensor_msgs::MagneticFieldConstPtr &msg)
{
        auto msg_copy=*msg;
    msg_copy.header.stamp=ros::Time::now();
        bag.write("/imu/mag", msg_copy.header.stamp, msg_copy);

}
