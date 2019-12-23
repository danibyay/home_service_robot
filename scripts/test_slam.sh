#!/bin/sh
source /opt/ros/kinetic/setup.bash
sleep 5
cd ~/catkin_ws2
roslaunch turtlebot_gazebo turtlebot_world.launch
