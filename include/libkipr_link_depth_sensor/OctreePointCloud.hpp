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
 * \file OctreePointCloud.hpp
 * \brief A point cloud using an octree as datastructure
 * \author Stefan Zeltner
 */

#ifndef _OCTREE_POINT_CLOUD_HPP_
#define _OCTREE_POINT_CLOUD_HPP_

#include <vector>

#include "octree/octree.h"
#include "libkipr_link_depth_sensor/PointCloud.hpp"
#include "libkipr_link_depth_sensor/DepthImageSize.hpp"

namespace libkipr_link_depth_sensor
{
  class OctreePointCloud : public PointCloud
  {
  public:
    /**
     * Creates an empty point cloud
	   *
	   * \param leave_size The leave size of the octree in mm
	   * \param nodes_per_edge Number of nodes per edge of the world cube.
	   *                       Must be a power of two
	   * \param depth_image_size The size of the depth image in pixel
     */
    OctreePointCloud(uint32_t leave_size, uint32_t nodes_per_edge, DepthImageSize depth_image_size);

    /* For memory handling */
    OctreePointCloud(const OctreePointCloud& other);
    OctreePointCloud(OctreePointCloud&& other);
    ~OctreePointCloud();
    OctreePointCloud& operator= (const OctreePointCloud& other);
    OctreePointCloud& operator= (OctreePointCloud&& other);
    
    /**
     * Adds a point to the point cloud
     *
     * \note: The memory ownership of point is transferred to this point
     *        cloud and the point is deleted once the cloud is deleted
     *
     * \param point Add this point to the cloud
     */
    virtual void addPoint(Point* point);
    
    /**
     * Gets a point specified by its depth coordinates
     *
     * \note: The returned pointer will point to an invalid location once the
     *        cloud is deleted
     *
     * \param depth_coord Depth image coordinate of this point
     * \returns The point or a nullptr if no point exists
     */
    virtual Point* getPointAtDepthCoordinate(DepthImageCoordinate depth_coord);
    
  private:
	  uint32_t leave_size_;
	  uint32_t nodes_per_edge_;
	  Octree<Point*> octree_;
    std::vector<Point*> points_2d_;
    DepthImageSize depth_image_size_;
  };
}

#endif /* _OCTREE_POINT_CLOUD_HPP_ */
