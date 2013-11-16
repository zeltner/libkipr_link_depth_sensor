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

#include <OpenNI.h>

/**
 * \file OpenNI2DepthMap.hpp
 * \brief OpenNI2 implementation of the OpenNI2DepthMap interface
 * \author Stefan Zeltner
 */

#ifndef _OPENNI2_DEPTH_MAP_HPP_
#define _OPENNI2_DEPTH_MAP_HPP_

#include "libkipr_link_depth_sensor/DepthMap.hpp"

namespace libkipr_link_depth_sensor
{
  class OpenNI2DepthMap : public DepthMap
  {
  public:
    OpenNI2DepthMap(openni::VideoFrameRef video_frame_ref);
    
    /**
    * Returns the height of the depth map in pixel
    *
    * \return Height of the depth map in pixel
    */
    virtual uint32_t getHeight() const;

    /**
    * Returns the width of the depth map in pixel
    *
    * \return Width of the depth map in pixel
    */
    virtual uint32_t getWidth() const;

    /**
    * Returns the distance value of the specified point.
    *
    * \param x X index of the point
    * \param y Y index of the point
    * \return The distance value
    */
    virtual uint32_t getDistanceAt(uint32_t x, uint32_t y) const;
  
  private:
    openni::VideoFrameRef video_frame_ref_;
  };
}

#endif /* _OPENNI2_DEPTH_MAP_HPP_ */
