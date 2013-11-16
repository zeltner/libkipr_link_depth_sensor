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

using namespace libkipr_link_depth_sensor;
using namespace openni;

OpenNI2DepthMap::OpenNI2DepthMap(openni::VideoFrameRef video_frame_ref)
  : video_frame_ref_(video_frame_ref)
{

}

uint32_t OpenNI2DepthMap::getDistanceAt(uint32_t width, uint32_t row) const
{
  return ((DepthPixel*)video_frame_ref_.getData())[width + row*video_frame_ref_.getWidth()];
}

uint32_t OpenNI2DepthMap::getWidth() const
{
  return video_frame_ref_.getWidth();
}

uint32_t OpenNI2DepthMap::getHeight() const
{
  return video_frame_ref_.getHeight();
}
