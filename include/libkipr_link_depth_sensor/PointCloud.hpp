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

#include <stdint.h>
#include <memory>
#include <functional>

#ifndef _POINT_CLOUD_HPP_
#define _POINT_CLOUD_HPP_

namespace libkipr_link_depth_sensor
{
  class PointCloud
  {
  public:
    typedef std::function<bool (uint32_t x, uint32_t y, uint32_t z)> Selector;
    
    /**
     * Returns a new PointCloud object containing a subset of points
     *
     * The select function specifies which points are kept. It is called for 
     * every point of this point cloud and if it returns true, the point is
     * copied into the new cloud.
     *
     * \param select The select function
     * \return A new PointCloud object
     */
    virtual std::shared_ptr<PointCloud> getSubCloud(Selector select) const = 0;
  };
}

#endif /* _POINT_CLOUD_HPP_ */
