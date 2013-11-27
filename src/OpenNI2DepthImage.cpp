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
#include "libkipr_link_depth_sensor/PointCloud.hpp"

using namespace libkipr_link_depth_sensor;
using namespace openni;

OpenNI2DepthImage::OpenNI2DepthImage(openni::VideoFrameRef video_frame_ref,
                                 const openni::VideoStream& stream)
  : video_frame_ref_(video_frame_ref), stream_(stream)
{

}

uint32_t OpenNI2DepthImage::getDepthAt(uint32_t x, uint32_t y) const
{
  return ((DepthPixel*)video_frame_ref_.getData())[x + y*video_frame_ref_.getWidth()];
}

uint32_t OpenNI2DepthImage::getWidth() const
{
  return video_frame_ref_.getWidth();
}

uint32_t OpenNI2DepthImage::getHeight() const
{
  return video_frame_ref_.getHeight();
}

std::shared_ptr<PointCloud> OpenNI2DepthImage::getPointCloud(Filter filter) const
{
  std::shared_ptr<PointCloud> point_cloud(new PointCloud());
  
  int depth_x, depth_y, depth_z;
  float world_x, world_y, world_z;
  Status rc;
  
  for(depth_x = 0; depth_x < video_frame_ref_.getWidth(); depth_x++)
  {
    for(depth_y = 0; depth_y < video_frame_ref_.getHeight(); depth_y++)
    {
      depth_z = getDepthAt(depth_x, depth_y);
      
      if(depth_z != 0)
      {
        if(filter(this, depth_x, depth_y, depth_z))
        {
          rc = CoordinateConverter::convertDepthToWorld(stream_, depth_x, depth_y, depth_z, &world_x, &world_y, &world_z);
          if(rc == STATUS_OK)
          {
            point_cloud->addPoint(Point(world_x, world_y, world_z));
          }
        }
      }
    }
  }
  
  return point_cloud;
}
