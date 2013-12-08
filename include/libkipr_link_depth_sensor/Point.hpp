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
 * \file Point.hpp
 * \brief This file describes the interface Point
 * \author Stefan Zeltner
 */

#ifndef _POINT_HPP_
#define _POINT_HPP_

#include <stdint.h>

#include "libkipr_link_depth_sensor/WorldCoordinate.hpp"
#include "libkipr_link_depth_sensor/DepthImageCoordinate.hpp"
#include "libkipr_link_depth_sensor/Color.hpp"

namespace libkipr_link_depth_sensor
{
  class Point
  {
  public:
    /**
     * Returns the world coordinate of the point
     *
     * \return The world coordinate of the point
     */
    virtual WorldCoordinate getWorldCoordinate() = 0;

    /**
     * Returns the depth image coordinate of the point
     *
     * \return The depth image coordinate of the point
     */
    virtual DepthImageCoordinate getDepthImageCoordinate() = 0;

    /**
     * Returns the depth value of the point
     *
     * \return The depth value of the point
     */
    virtual int32_t getDepth() = 0;

    /**
     * Returns the color of the point
     *
     * \return The color of the point
     */
    virtual Color getColor() = 0;

    /**
     * Sets the color of the point
     *
     * \param color The color of the point
     */
    virtual void setColor(const Color& color) = 0;
    
    /**
     * Creates a clone of an point
     *
     * \return A pointer to the new point
     */
    virtual Point* clone() const = 0;
  };
}

#endif /* _POINT_HPP_ */
