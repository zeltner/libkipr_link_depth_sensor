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

#include "libkipr_link_depth_sensor/OpenNI2PointCloud.hpp"

using namespace libkipr_link_depth_sensor;
using namespace openni;

OpenNI2PointCloud::OpenNI2PointCloud(openni::VideoFrameRef video_frame_ref)
  : OpenNI2PointCloud(video_frame_ref,
    [](uint32_t x, uint32_t y, uint32_t z) { return true; })
{

}

OpenNI2PointCloud::OpenNI2PointCloud(openni::VideoFrameRef video_frame_ref,
                                     Selector selector)
  : video_frame_ref_(video_frame_ref), selector_(selector)
{

}

std::shared_ptr<PointCloud> OpenNI2PointCloud::getSubCloud(Selector select) const
{
  return std::shared_ptr<PointCloud>(new OpenNI2PointCloud(video_frame_ref_, 
                                                           select));
}
