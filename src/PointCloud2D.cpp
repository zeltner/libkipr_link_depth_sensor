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

#include "libkipr_link_depth_sensor/PointCloud2D.hpp"

using namespace libkipr_link_depth_sensor;

PointCloud2D::PointCloud2D(DepthImageSize depth_image_size)
  : points_2d_((depth_image_size.width * depth_image_size.height), nullptr),
    depth_image_size_(depth_image_size), bounding_box_()
{

}

PointCloud2D::PointCloud2D(const PointCloud2D& other)
  : points_2d_((other.depth_image_size_.width * other.depth_image_size_.height), nullptr),
    depth_image_size_(other.depth_image_size_), bounding_box_()
{
  std::for_each(other.points_2d_.begin(), other.points_2d_.end(), [this](Point* point)
    {
      addPoint(new Point(*point));
    });
}

PointCloud2D::PointCloud2D(PointCloud2D&& other)
  : points_2d_(other.points_2d_),
    depth_image_size_(other.depth_image_size_), bounding_box_()
{
  other.points_2d_ = std::vector<Point*>();
}

PointCloud2D::~PointCloud2D()
{
  std::for_each(points_2d_.begin(), points_2d_.end(), [](Point* point)
    {
      delete point;
    });
}

PointCloud2D& PointCloud2D::operator= (const PointCloud2D& other)
{
  points_2d_ = std::vector<Point*>((other.depth_image_size_.width * other.depth_image_size_.height), nullptr);
  depth_image_size_ = other.depth_image_size_;
  
  std::for_each(other.points_2d_.begin(), other.points_2d_.end(), [this](Point* point)
    {
      addPoint(new Point(*point));
    });

  return *this;
}

PointCloud2D& PointCloud2D::operator= (PointCloud2D&& other)
{
  points_2d_ =  other.points_2d_;
  depth_image_size_ = other.depth_image_size_;
  
  other.points_2d_ = std::vector<Point*>();

  return *this;
}

void PointCloud2D::addPoint(Point* point)
{
  DepthImageCoordinate depth_coord = point->getDepthImageCoordinate();

  bounding_box_.add(*point);

  points_2d_[depth_coord.y * depth_image_size_.width + depth_coord.x] = point;
}

Point* PointCloud2D::getPointAtDepthCoordinate(DepthImageCoordinate depth_coord)
{
  return points_2d_[depth_coord.y * depth_image_size_.width + depth_coord.x];
}

BoundingBox PointCloud2D::getBoundingBox()
{
  return bounding_box_;
}
