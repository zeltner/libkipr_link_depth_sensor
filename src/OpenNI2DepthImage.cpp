/* *****************************************************************************

    This file is part of the depth sensor library for the
        KIPR Link Robot Controller.

    libkipr_link_depth_sensor is free software: you can redistribute it and/or
    modify it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    libkipr_link_depth_sensor is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with libkipr_link_depth_sensor.
    If not, see <http://www.gnu.org/licenses/>.

*******************************************************************************/

#include "libkipr_link_depth_sensor/OpenNI2DepthImage.hpp"
#include "libkipr_link_depth_sensor/Exception.hpp"
#include "libkipr_link_depth_sensor/PointCloud2D.hpp"

using namespace libkipr_link_depth_sensor;
using namespace openni;

OpenNI2DepthImage::OpenNI2DepthImage(openni::VideoFrameRef video_frame_ref,
                                 const openni::VideoStream& stream)
  : video_frame_ref_(video_frame_ref), stream_(stream),
    size_(video_frame_ref_.getWidth(), video_frame_ref_.getHeight())
{

}

int32_t OpenNI2DepthImage::getDepthAt(const DepthImageCoordinate& coordinate) const
{
  return ((DepthPixel*)video_frame_ref_.getData())[coordinate.x + coordinate.y*size_.width];
}

uint32_t OpenNI2DepthImage::getWidth() const
{
  return size_.width;
}

uint32_t OpenNI2DepthImage::getHeight() const
{
  return size_.height;
}

PointCloud* OpenNI2DepthImage::getPointCloud(Filter filter) const
{
  PointCloud* point_cloud = new PointCloud2D(size_);
  
  int depth_x, depth_y, depth_z;
  float world_x, world_y, world_z;
  
  for(depth_y = 0; depth_y < (int) size_.height; depth_y++)
  {
    for(depth_x = 0; depth_x < (int) size_.width; depth_x++)
    {
      DepthImageCoordinate depth_coord(depth_x, depth_y);
      depth_z = getDepthAt(depth_coord);
      
      if(depth_z != 0)
      {
        Status rc = CoordinateConverter::convertDepthToWorld(stream_, 
          depth_coord.x, depth_coord.y, depth_z, &world_x, &world_y, &world_z);
        if(rc != STATUS_OK)
        {
          throw Exception(std::string("Coordinate conversion failed with ")
            + OpenNI::getExtendedError());
        }
        
        point_cloud->addPoint(new Point(
          WorldCoordinate((int32_t) world_x, (int32_t) world_y, (int32_t) world_z),
          depth_coord, depth_z));
      }
    }
  }
  
  return point_cloud;
}
