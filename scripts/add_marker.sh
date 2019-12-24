#!/bin/sh
pkill -f ros
pkill -f rviz
pkill -f gazebo
cd ~/catkin_ws
sleep 5
xterm -T "Turtlebot" -e " roslaunch turtlebot_gazebo turtlebot_world.launch" &
sleep 5
xterm -T "gmapping" -e "roslaunch turtlebot_gazebo amcl_demo.launch" &
sleep 5
xterm -T "rviz" -e "roslaunch turtlebot_rviz_launchers view_navigation.launch" &
sleep 5
xterm -T "pick_objects" -e "roslaunch add_markers add_markers.launch"
