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
 * \file OpenNI2DepthMap.hpp
 * \brief OpenNI2 implementation of the DepthMap interface
 * \author Stefan Zeltner
 */

#ifndef _OPENNI2_DEPTH_MAP_HPP_
#define _OPENNI2_DEPTH_MAP_HPP_

#include <OpenNI.h>

#include "libkipr_link_depth_sensor/DepthMap.hpp"

namespace libkipr_link_depth_sensor
{
  class OpenNI2DepthMap : public DepthMap
  {
  public:
    OpenNI2DepthMap(openni::VideoFrameRef video_frame_ref,
                    const openni::VideoStream& stream);
    
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
    * Returns the depth value of the specified point.
    *
    * \param x X index of the point
    * \param y Y index of the point
    * \return The depth value
    */
    virtual uint32_t getDepthAt(uint32_t x, uint32_t y) const;
    
    /**
     * Returns a PointCloud object of this depth map
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
    virtual std::shared_ptr<PointCloud> getPointCloud(Filter filter) const;
  
  private:
    openni::VideoFrameRef video_frame_ref_;
    const openni::VideoStream& stream_;
  };
}

#endif /* _OPENNI2_DEPTH_MAP_HPP_ */
