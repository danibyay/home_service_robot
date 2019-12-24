#include <ros/ros.h>
#include <visualization_msgs/Marker.h>

int main( int argc, char** argv )
{
  ros::init(argc, argv, "add_markers");
  ros::NodeHandle n;
  ros::Rate r(1);
  ros::Publisher marker_pub = n.advertise<visualization_msgs::Marker>("visualization_marker", 1);

  // Set our initial shape type to be a cube
  uint32_t shape = visualization_msgs::Marker::CUBE;

  ros::spinOnce();
  visualization_msgs::Marker marker;
  // Set the frame ID and timestamp.  See the TF tutorials for information on these.
  marker.header.frame_id = "map";
  marker.header.stamp = ros::Time::now();

  // Set the namespace and id for this marker
  marker.ns = "my_cube";
  marker.id = 0;

  // Set the marker type.  Initially this is CUBE, and cycles between that and SPHERE, ARROW, and CYLINDER
  marker.type = shape;

  // Set the marker action.  Options are ADD, DELETE, and new in ROS Indigo: 3 (DELETEALL)
  marker.action = visualization_msgs::Marker::ADD;

  // Set the pose of the marker. (x,y,z) (x,y,z,w)
  marker.pose.position.x = 1;
  marker.pose.position.y = 0;
  marker.pose.position.z = 0;
  marker.pose.orientation.x = 0.0;
  marker.pose.orientation.y = 0.0;
  marker.pose.orientation.z = 0.0;
  marker.pose.orientation.w = 1.0;

  // Set the scale of the marker in meters
  marker.scale.x = 0.2;
  marker.scale.y = 0.2;
  marker.scale.z = 1.0;

  // Set the color
  marker.color.r = 1.0f;
  marker.color.g = 0.0f;
  marker.color.b = 0.0f;
  marker.color.a = 1.0;

  marker.lifetime = ros::Duration();

  // Publish the marker
  while (marker_pub.getNumSubscribers() < 1) {
    if (!ros::ok()) {
      return 0;
    }
    ROS_WARN_ONCE("Please create a subscriber to the marker");
    sleep(1);
  }

  marker_pub.publish(marker);
  ROS_INFO("publish at pick up location");

  std::string Robot_pos;
  while (ros::ok()) {
    if (ros::param::get("/Robot_pos", Robot_pos)) {

      if (Robot_pos == "position_1") {
        // We've reached position one, simulate picking up the object
        marker.action = visualization_msgs::Marker::DELETE;
        marker_pub.publish(marker);
        ROS_INFO("Reached position 1, hiding marker");
        ros::Duration(5.0).sleep();
      }

      if (Robot_pos == "position_2") {
        // We've reached position two, simulate dropping the object.
        marker.pose.position.x = -0.31;
        marker.pose.position.y = -0.22;
        marker.pose.orientation.z = 0.99;
        marker.pose.orientation.w = 0.009;
        marker.action = visualization_msgs::Marker::ADD;
        marker_pub.publish(marker);
        ROS_INFO("Reached position 2, publish at drop off location");
      }

    }
  }

  r.sleep();

}
