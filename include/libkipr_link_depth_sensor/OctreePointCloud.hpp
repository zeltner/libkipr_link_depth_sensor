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

#include <libkipr_link_depth_sensor/PointCloud.hpp>

namespace libkipr_link_depth_sensor
{
  class OctreePointCloud : public PointCloud
  {
  public:
    typedef std::function<bool (const Point& point)> Filter;
    
    /**
     * Creates an empty point cloud
     */
    OctreePointCloud();
    
    /**
     * Creates a point cloud from a list of points
     *
     * The filter function specifies which points are kept. It is called for 
     * every point of this point cloud and if it returns true, the point is
     * copied into the list.
     *
     * \param points A list of points
     * \param filter The filter function
     */
    OctreePointCloud(const std::list<Point>& points, Filter filter);
    
    /**
     * Adds a point to the point cloud
     *
     * \param point Add this point to the cloud
     */
    void addPoint(const Point& point);
    
    /**
     * Returns a new OctreePointCloud object containing a subset of points
     *
     * The filter function specifies which points are kept. It is called for 
     * every point of this point cloud and if it returns true, the point is
     * copied into the new cloud.
     *
     * \param filter The filter function
     * \return A new OctreePointCloud object
     */
    std::shared_ptr<PointCloud> getSubCloud(Filter filter) const;
    
    /**
     * Returns a list of all points
     *
     * The filter function specifies which points are kept. It is called for 
     * every point of this point cloud and if it returns true, the point is
     * copied into the list.
     *
     * \note This function creates no copy of the point list!
     *
     * \return A list of all points
     */
    std::shared_ptr<const std::list<Point>> getPoints() const;
    
    /**
     * Returns a list of all points
     *
     * The filter function specifies which points are kept. It is called for 
     * every point of this point cloud and if it returns true, the point is
     * copied into the list.
     *
     * \note This function creates a copy of the point list!
     *
     * \param filter The filter function
     * \return A list of all points
     */
    std::shared_ptr<std::list<Point>> getPoints(Filter filter) const;
    
  private:
    std::shared_ptr<std::list<Point>> points_;
  };
}

#endif /* _OCTREE_POINT_CLOUD_HPP_ */
