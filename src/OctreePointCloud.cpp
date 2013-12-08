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

#include "libkipr_link_depth_sensor/OctreePointCloud.hpp"

using namespace libkipr_link_depth_sensor;

OctreePointCloud::OctreePointCloud(uint32_t leave_size, uint32_t nodes_per_edge, DepthImageSize depth_image_size)
  : leave_size_(leave_size), nodes_per_edge_(nodes_per_edge),
    octree_(nodes_per_edge, nullptr),
    points_2d_((depth_image_size.width * depth_image_size.height), nullptr),
    depth_image_size_(depth_image_size)
{

}

OctreePointCloud::OctreePointCloud(const OctreePointCloud& other)
  : leave_size_(other.leave_size_), nodes_per_edge_(other.nodes_per_edge_),
    octree_(nodes_per_edge_, nullptr),
    points_2d_((other.depth_image_size_.width * other.depth_image_size_.height), nullptr),
    depth_image_size_(other.depth_image_size_)
{
  std::for_each(other.points_2d_.begin(), other.points_2d_.end(), [this](Point* point)
    {
      addPoint(point->clone());
    });
}

OctreePointCloud::OctreePointCloud(OctreePointCloud&& other)
  : leave_size_(other.leave_size_), nodes_per_edge_(other.nodes_per_edge_),
    octree_(other.octree_),
    points_2d_(other.points_2d_),
    depth_image_size_(other.depth_image_size_)
{
  other.octree_  = Octree<Point*>(nodes_per_edge_, nullptr);
  other.points_2d_ = std::vector<Point*>();
}

OctreePointCloud::~OctreePointCloud()
{
  std::for_each(points_2d_.begin(), points_2d_.end(), [](Point* point)
    {
      delete point;
    });
}

OctreePointCloud& OctreePointCloud::operator= (const OctreePointCloud& other)
{
  leave_size_ = other.leave_size_;
  nodes_per_edge_ = other.nodes_per_edge_;
  octree_ = Octree<Point*>(nodes_per_edge_, nullptr);
  points_2d_ = std::vector<Point*>((other.depth_image_size_.width * other.depth_image_size_.height), nullptr);
  depth_image_size_ = other.depth_image_size_;
  
  std::for_each(other.points_2d_.begin(), other.points_2d_.end(), [this](Point* point)
    {
      addPoint(point->clone());
    });

  return *this;
}

OctreePointCloud& OctreePointCloud::operator= (OctreePointCloud&& other)
{
  leave_size_ = other.leave_size_;
  nodes_per_edge_ = other.nodes_per_edge_;
  octree_ =  other.octree_;
  points_2d_ =  other.points_2d_;
  depth_image_size_ = other.depth_image_size_;
  
  other.octree_ = Octree<Point*>(nodes_per_edge_, nullptr);
  other.points_2d_ = std::vector<Point*>();

  return *this;
}

void OctreePointCloud::addPoint(Point* point)
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
  points_2d_[depth_coord.y * depth_image_size_.width + depth_coord.x] = point;
}

Point* OctreePointCloud::getPointAtDepthCoordinate(DepthImageCoordinate depth_coord)
{
  return points_2d_[depth_coord.y * depth_image_size_.width + depth_coord.x];
}
