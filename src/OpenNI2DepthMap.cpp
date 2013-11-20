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

#include "libkipr_link_depth_sensor/OpenNI2DepthMap.hpp"
#include "libkipr_link_depth_sensor/PointCloud.hpp"

using namespace libkipr_link_depth_sensor;
using namespace openni;

OpenNI2DepthMap::OpenNI2DepthMap(openni::VideoFrameRef video_frame_ref,
                                 const openni::VideoStream& stream)
  : video_frame_ref_(video_frame_ref), stream_(stream)
{

}

uint32_t OpenNI2DepthMap::getDistanceAt(uint32_t x, uint32_t y) const
{
  return ((DepthPixel*)video_frame_ref_.getData())[x + y*video_frame_ref_.getWidth()];
}

uint32_t OpenNI2DepthMap::getWidth() const
{
  return video_frame_ref_.getWidth();
}

uint32_t OpenNI2DepthMap::getHeight() const
{
  return video_frame_ref_.getHeight();
}

std::shared_ptr<PointCloud> OpenNI2DepthMap::getPointCloud() const
{
  int depth_x, depth_y, depth_z;
  float world_x, world_y, world_z;
  Status rc;
  
  for(depth_x = 0; depth_x < video_frame_ref_.getWidth(); depth_x++)
  {
    for(depth_y = 0; depth_y < video_frame_ref_.getHeight(); depth_y++)
    {
      depth_z = getDistanceAt(depth_x, depth_y);

      rc = CoordinateConverter::convertDepthToWorld(stream_, depth_x, depth_y, depth_z, &world_x, &world_y, &world_z);
      if(rc != STATUS_OK)
      {
        printf("[%d, %d, %d] --> N/A\n", depth_x, depth_y, depth_z);
      }
      else
      {
        printf("[%d, %d, %d] --> [%d, %d, %d]\n", depth_x, depth_y, depth_z, (int) world_x, (int) world_y, (int) world_z);
      }
    }
  }
  
  return std::shared_ptr<PointCloud>(new PointCloud());
}
