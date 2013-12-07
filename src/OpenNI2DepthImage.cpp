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
#include "libkipr_link_depth_sensor/OpenNI2Point.hpp"
#include "libkipr_link_depth_sensor/OctreePointCloud.hpp"

using namespace libkipr_link_depth_sensor;
using namespace openni;

OpenNI2DepthImage::OpenNI2DepthImage(openni::VideoFrameRef video_frame_ref,
                                 const openni::VideoStream& stream)
  : video_frame_ref_(video_frame_ref), stream_(stream)
{

}

int32_t OpenNI2DepthImage::getDepthAt(const DepthImageCoordinate& coordinate) const
{
  return ((DepthPixel*)video_frame_ref_.getData())[coordinate.x + coordinate.y*video_frame_ref_.getWidth()];
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
  // TODO: assume a world of 4098 x 4098 x 4098 mm with 256 points per edge
  uint32_t leave_size = 8 /* mm */;
  uint32_t nodes_per_edge = 256;

  std::shared_ptr<PointCloud> point_cloud(new OctreePointCloud(leave_size, nodes_per_edge));
  
  int depth_x, depth_y, depth_z;
  
  for(depth_x = 0; depth_x < video_frame_ref_.getWidth(); depth_x++)
  {
    for(depth_y = 0; depth_y < video_frame_ref_.getHeight(); depth_y++)
    {
      DepthImageCoordinate depth_coord(depth_x, depth_y);

      depth_z = getDepthAt(depth_coord);
      
      if(depth_z != 0)
      {
        if(filter(this, depth_coord, depth_z))
        {
          point_cloud->addPoint(std::shared_ptr<Point>(new OpenNI2Point(depth_coord, video_frame_ref_, stream_)));
        }
      }
    }
  }
  
  return point_cloud;
}
