#include <ros/ros.h>
#include <ros/package.h>
#include <string>
#include <iostream>

#include <geometry_msgs/Pose.h>
#include <geometry_msgs/PoseArray.h>
#include <geometry_msgs/Vector3.h>
#include <geometry_msgs/PoseStamped.h>

#include <eigen3/Eigen/Eigen>

#include <apriltag_ros/AprilTagDetectionArray.h>

geometry_msgs::Pose hand_L, hand_R;
ros::Publisher pub_hand_pose_R_, pub_hand_pose_L_;

void callback_marker_pose(const apriltag_ros::AprilTagDetectionArray::ConstPtr& msg)
{
  for(int i = 0; i < msg->detections.size(); i++)
  {
    if(msg->detections[i].id[0] == 4)
    {
      hand_L = msg->detections[i].pose.pose.pose;
      pub_hand_pose_L_.publish(hand_L);
    }
    else if(msg->detections[i].id[0] == 5)
    {
      hand_R = msg->detections[i].pose.pose.pose;
      pub_hand_pose_R_.publish(hand_R);
    }
  }
}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "pub_hand_marker_node");
  ros::NodeHandle n;
  ros::Rate rate(100);

  ros::Subscriber sub_marker_pose = n.subscribe("/tag_detections", 1, callback_marker_pose);
  pub_hand_pose_R_ = n.advertise<geometry_msgs::Pose>("Yumi_RIGHT/hand_pose", 1);
  pub_hand_pose_L_ = n.advertise<geometry_msgs::Pose>("Yumi_LEFT/hand_pose", 1);
 


  while(ros::ok())
    {
      ros::spinOnce();
      rate.sleep();
    }

  return 0;
}