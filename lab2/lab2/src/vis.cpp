#include <ros/ros.h>
#include <sensor_msgs/LaserScan.h>
#include <visualization_msgs/Marker.h>

#include <cmath>

ros::Publisher laser_scan_pub;

void pointCallback(const sensor_msgs::LaserScan& msg)
{
         visualization_msgs::Marker points;
          points.header.frame_id = "/base_link" ;

          points.header.stamp =ros::Time::now() ;
          



          points.ns = "points" ;
          points.pose.orientation.w = 1;
          points.id = 0;
          points.type = visualization_msgs::Marker::POINTS;
          points.scale.x = 0.05;
          points.scale.y = 0.05;
          points.color.g = 1;
          points.color.a = 1;

          double a = 0;       


          for(int i=0; i<361; i++)
           {  geometry_msgs::Point p;

              
              a = a + 0.00872664619237 ;

              
     
              p.x = msg.ranges[i]*cos(a) ; 
              p.y = msg.ranges[i]*sin(a) ;
              p.z = 0 ;
              points.points.push_back(p) ;

              std::cout << p.x << ", " << p.y << std::endl;
 
                }

         
           laser_scan_pub.publish(points);
}



int main(int argc, char **argv)
{




 ros::init(argc, argv, "data_gather");
 ros::NodeHandle n;

 ros::Subscriber sub = n.subscribe("/base_scan", 50, &pointCallback);

ros::NodeHandle r;

laser_scan_pub = r.advertise<visualization_msgs::Marker>("visualization_marker", 50);

 ros::spin();

 return 0;
}







