#include "ros/ros.h"
#include "std_msgs/Float64.h"

#include <math.h>


float X_current;
float X_previous;

void joint1angleCallback(const std_msgs::Float64 msg)
{      
      X_current = msg.data;
      ROS_INFO("X: %f", X_current);
      
      if (X_current > X_previous){
		  X_previous = X_current;
	  } else {
		  X_current = X_previous;
	  }
      
}


int main(int argc, char **argv){
ros::init(argc, argv, "rotate");
ros::NodeHandle nh;

X_previous = -10;

ros::Publisher pub3 = nh.advertise<std_msgs::Float64>("/robot/joint1_position_controller/command", 100);

//before i tried to use some other name, "joint1_ulugbek" for example. But it didn't work. 
//only in this way the robot responds
ros::Subscriber sub = nh.subscribe("/robot/joint1_position_controller/command", 1000, joint1angleCallback);


ros::Rate loop_rate(10);

ros::Time startTime = ros::Time::now(); 

         while (ros::ok()){
                 std_msgs::Float64 msg_to_send;


                 msg_to_send.data = X_current;
                 
                 pub3.publish(msg_to_send);
 
                 ROS_INFO("moving joint 1");

                 ros::spinOnce();

                 loop_rate.sleep();
         }
}
