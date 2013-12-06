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
 * \file PointCloud.hpp
 * \brief The interface for a point cloud
 * \author Stefan Zeltner
 */

#ifndef _POINT_CLOUD_HPP_
#define _POINT_CLOUD_HPP_

#include <memory>

#include <libkipr_link_depth_sensor/Point.hpp>

namespace libkipr_link_depth_sensor
{
  class PointCloud
  {
  public:
    /**
     * Adds a point to the point cloud
     *
     * \param point Add this point to the cloud
     */
    virtual void addPoint(std::shared_ptr<Point> point) = 0;

    /**
     * Gets a point specified by its depth coordinates
     *
     * \param depth_x X coordinate of this point
     * \param depth_y Y coordinate of this point
     *
     * \returns The point or a nullpointer if no point exists
     */
    virtual std::shared_ptr<Point> getPointAtDepthCoordinate(uint32_t depth_x,
                                                             uint32_t depth_y) = 0;
  };
}

#endif /* _POINT_CLOUD_HPP_ */
