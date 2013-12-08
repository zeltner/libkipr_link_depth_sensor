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

/**
 * \file OpenNI2Point.hpp
 * \brief This file describes the OpenNI2 implementation of the interface Point
 * \author Stefan Zeltner
 */

#ifndef _OPENNI2_POINT_HPP_
#define _OPENNI2_POINT_HPP_

#include <OpenNI.h>

#include "libkipr_link_depth_sensor/Point.hpp"

namespace libkipr_link_depth_sensor
{
  class OpenNI2Point : public Point
  {
  public:
    OpenNI2Point(const DepthImageCoordinate depth_coord,
      openni::VideoFrameRef video_frame_ref,
      const openni::VideoStream& stream);

    /**
     * Returns the world coordinate of the point
     *
     * \return The world coordinate of the point
     */
    virtual WorldCoordinate getWorldCoordinate();

    /**
     * Returns the depth image coordinate of the point
     *
     * \return The depth image coordinate of the point
     */
    virtual DepthImageCoordinate getDepthImageCoordinate();

    /**
     * Returns the depth value of the point
     *
     * \return The depth value of the point
     */
    virtual int32_t getDepth();

    /**
     * Returns the color of the point
     *
     * \return The color of the point
     */
    virtual Color getColor();

    /**
     * Sets the color of the point
     *
     * \param color The color of the point
     */
    virtual void setColor(const Color& color);
    
    /**
     * Creates a clone of an point
     *
     * \return A pointer to the new point
     */
    virtual Point* clone() const;

  private:
    openni::VideoFrameRef video_frame_ref_;
    const openni::VideoStream& stream_;

    DepthImageCoordinate depth_coord_;
    int32_t depth_;

    bool world_coord_is_calc_;
    WorldCoordinate world_coord_;

    Color color_;
  };
}

#endif /* _OPENNI2_POINT_HPP_ */
