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
 * \file DepthImage.hpp
 * \brief The interface for a depth image
 * \author Stefan Zeltner
 */

#include <stdint.h>
#include <memory>

#include "libkipr_link_depth_sensor/PointCloud.hpp"

#ifndef _DEPTH_IMAGE_HPP_
#define _DEPTH_IMAGE_HPP_

namespace libkipr_link_depth_sensor
{
  class DepthImage
  {
  public:
    typedef std::function<bool (const DepthImage* _this,
      int x, int y, int& depth)> Filter;
    
    /**
     * Returns the height of the depth image in pixel
     *
     * \return Height of the depth image in pixel
     */
    virtual uint32_t getHeight() const = 0;

    /**
     * Returns the width of the depth image in pixel
     *
     * \return Width of the depth image in pixel
     */
    virtual uint32_t getWidth() const = 0;

    /**
     * Returns the depth value of the specified point.
     *
     * \param x X index of the point
     * \param y Y index of the point
     * \return The depth value
     */
    virtual uint32_t getDepthAt(uint32_t x, uint32_t y) const = 0;
    
    /**
     * Returns a PointCloud object of this depth image
     *
     * The filter function is used to add only points to the point cloud
     * which meet the filter criteria. In addition it can be used to modify the
     * depth value (e.g. average over the surrounding pixel) before put them
     * into the point cloud. The _this parameter of the filter can be used to
     * get the depth of the surrounding pixel via getDepthAt()
     *
     * \note Creating a point cloud is very expensive. Therefore the filter
     * should filter out as much as possible.
     *
     * \return A PointCloud object
     */
    virtual std::shared_ptr<PointCloud> getPointCloud(Filter filter) const = 0;
  };
}

#endif /* _DEPTH_IMAGE_HPP_ */