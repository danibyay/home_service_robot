#!/bin/sh
pkill -f ros
pkill -f rviz
pkill -f gazebo
cd ~/catkin_ws2
source devel/setup.bash
sleep 5
xterm -T "Turtlebot" -e " roslaunch turtlebot_gazebo turtlebot_world.launch" &
sleep 5
xterm -T "gmapping" -e "roslaunch turtlebot_gazebo gmapping_demo.launch" &
sleep 5
xterm -T "rviz" -e "roslaunch turtlebot_rviz_launchers view_navigation.launch" &
sleep 5
xterm -T "teleop" -e "roslaunch turtlebot_teleop keyboard_teleop.launch"
