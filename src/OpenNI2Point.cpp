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

#include "libkipr_link_depth_sensor/Exception.hpp"
#include "libkipr_link_depth_sensor/OpenNI2Point.hpp"

using namespace libkipr_link_depth_sensor;
using namespace openni;

OpenNI2Point::OpenNI2Point(const DepthImageCoordinate depth_coord,
      openni::VideoFrameRef video_frame_ref,
      const openni::VideoStream& stream)
      : video_frame_ref_(video_frame_ref),
        stream_(stream),
        depth_coord_(depth_coord),
        depth_(((DepthPixel*)video_frame_ref_.getData())[depth_coord.x + depth_coord.y*video_frame_ref_.getWidth()]),
        world_coord_is_calc_(false),
        world_coord_(0, 0, 0),
        color_(0xFF, 0xFF, 0xFF)
{

}

WorldCoordinate OpenNI2Point::getWorldCoordinate()
{
  if(!world_coord_is_calc_)
  {
    float world_x, world_y, world_z;

    Status rc = CoordinateConverter::convertDepthToWorld(stream_,
      depth_coord_.x, depth_coord_.y, depth_, &world_x, &world_y, &world_z);
    if(rc != STATUS_OK)
    {
    throw Exception(std::string("Coordinate conversion failed with ")
      + OpenNI::getExtendedError());
    }

    world_coord_ = WorldCoordinate((int32_t) world_x, (int32_t) world_y, (int32_t) world_z);
    world_coord_is_calc_ = true;
  }
  
  return world_coord_;
}

DepthImageCoordinate OpenNI2Point::getDepthImageCoordinate()
{
  return depth_coord_;
}

int32_t OpenNI2Point::getDepth()
{
  return depth_;
}

Color OpenNI2Point::getColor()
{
  return color_;
}

void OpenNI2Point::setColor(const Color& color)
{
  color_ = color;
}

Point* OpenNI2Point::clone() const
{
  return new OpenNI2Point(*this);
}
