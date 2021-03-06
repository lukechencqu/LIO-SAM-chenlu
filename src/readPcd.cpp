// #includ <ros/ros.h>

// int main(int argc, char** argv)
// {
//     ros::init(argc, argv, "recognition");

//     return true;
// }

#include <ros/ros.h>

#include <pcl/io/pcd_io.h>
#include <pcl/point_cloud.h>
#include <pcl/visualization/pcl_visualizer.h>
#include <pcl/console/parse.h>

typedef pcl::PointXYZ PointType;

std::string model_filename_;
std::string scene_filename_;



void
parseCommandLine (int argc, char *argv[])
{

  //Model & scene filenames
  std::vector<int> filenames;
  filenames = pcl::console::parse_file_extension_argument (argc, argv, ".pcd");
  if (filenames.size () != 1)
  {
    std::cout << "Filenames missing.\n";
    exit (-1);
  }

  scene_filename_ = argv[filenames[0]];

}

int main (int argc, char *argv[])
{
  ros::init(argc, argv, "correspondence_grouping");
  ros::NodeHandle nh;

  parseCommandLine (argc, argv);

  pcl::PointCloud<PointType>::Ptr model (new pcl::PointCloud<PointType> ());
  pcl::PointCloud<PointType>::Ptr model_keypoints (new pcl::PointCloud<PointType> ());
  pcl::PointCloud<PointType>::Ptr scene (new pcl::PointCloud<PointType> ());

  //
  //  Load clouds
  //
  if (pcl::io::loadPCDFile (scene_filename_, *scene) < 0)
  {
    std::cout << "Error loading scene cloud." << std::endl;
    return (-1);
  }


  //
  //  Visualization
  //
  pcl::visualization::PCLVisualizer viewer ("Map Viewer");
  pcl::visualization::PointCloudColorHandlerGenericField<pcl::PointXYZ> fildColor(scene, "z"); // 按照z字段进行渲染  
  viewer.addPointCloud (scene, fildColor, "scene_cloud");

  while (!viewer.wasStopped ())
  {
    viewer.spinOnce ();
  }

  return (0);
}