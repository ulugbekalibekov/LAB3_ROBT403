#include "ros/ros.h"
#include "std_msgs/Float64.h"

#include <math.h>


float sin_function;

float time_interval;

void joint1angleCallback(const std_msgs::Float64 msg)
{     
	
      sin_function = msg.data;
      ROS_INFO("Sin: %f", sin_function);
      
}


int main(int argc, char **argv){
ros::init(argc, argv, "rotate");
ros::NodeHandle nh;

time_interval = 0;

ros::Publisher pub3 = nh.advertise<std_msgs::Float64>("/robot/joint5_position_controller/command", 100);

//before i tried to use some other name, "joint1_ulugbek" for example. But it didn't work. 
//only in this way the robot responds
ros::Subscriber sub = nh.subscribe("/robot/joint5_position_controller/command", 1000, joint1angleCallback);


ros::Rate loop_rate(1);

ros::Time startTime = ros::Time::now(); 

         while (ros::ok()){
			 
                 std_msgs::Float64 msg_to_send;
                 
                       sin_function = sin(time_interval);
                       
					   time_interval = time_interval + 0.1;


                 msg_to_send.data = sin_function;
                 
                 pub3.publish(msg_to_send);
 
                 ROS_INFO("moving joint 5");

                 ros::spinOnce();

                 loop_rate.sleep();
         }
}
