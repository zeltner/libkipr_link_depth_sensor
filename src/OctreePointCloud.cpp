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

#include <algorithm>

#include "libkipr_link_depth_sensor/OctreePointCloud.hpp"

using namespace libkipr_link_depth_sensor;

OctreePointCloud::OctreePointCloud(uint32_t leave_size, uint32_t nodes_per_edge)
  : leave_size_(leave_size), nodes_per_edge_(nodes_per_edge),
	  octree_(nodes_per_edge, std::shared_ptr<Point>())
{

}

void OctreePointCloud::addPoint(std::shared_ptr<Point> point)
{
  int half_world_size = leave_size_ * nodes_per_edge_ / 2;
  WorldCoordinate world_coord = point->getWorldCoordinate();
  DepthImageCoordinate depth_coord = point->getDepthImageCoordinate();
  int32_t depth = point->getDepth();

  int tree_x = (half_world_size + world_coord.x) / leave_size_;
  if(tree_x < 0 || tree_x >= (int32_t) nodes_per_edge_)
  {
    point->setColor(Color(0xFF, 0xFF, 0xFF));
    return;
  }
  
  int tree_y = (half_world_size + world_coord.y) / leave_size_;
  if(tree_y < 0 || tree_y >= (int32_t) nodes_per_edge_)
  {
    point->setColor(Color(0xFF, 0xFF, 0xFF));
    return;
  }
  
  int tree_z = depth / leave_size_;
  if(tree_z < 0 || tree_z >= (int32_t) nodes_per_edge_)
  {
    point->setColor(Color(0xFF, 0xFF, 0xFF));
    return;
  }

  point->setColor(Color(0xFF * tree_x / nodes_per_edge_,
    0xFF * tree_y / nodes_per_edge_,  0xFF * tree_z / nodes_per_edge_));

  octree_(tree_x, tree_y, tree_z) = point;
  points_2d_[depth_coord.y][depth_coord.x] = point;
}

std::shared_ptr<Point> OctreePointCloud::getPointAtDepthCoordinate(uint32_t depth_x,
                                                                   uint32_t depth_y)
{
  return points_2d_[depth_y][depth_x];
}
