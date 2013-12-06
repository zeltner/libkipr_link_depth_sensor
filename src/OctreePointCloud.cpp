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

#include <libkipr_link_depth_sensor/OctreePointCloud.hpp>

using namespace libkipr_link_depth_sensor;

OctreePointCloud::OctreePointCloud()
{

}

OctreePointCloud::OctreePointCloud(const std::list<Point>& points, Filter filter)
{
  std::copy_if(points.begin(), points.end(), points_->begin(), filter);
}

void OctreePointCloud::addPoint(const Point& point)
{
  points_->push_back(point);
}

std::shared_ptr<PointCloud> OctreePointCloud::getSubCloud(Filter filter) const
{
  return std::shared_ptr<OctreePointCloud>(new OctreePointCloud(*points_, filter));
}

std::shared_ptr<const std::list<Point>> OctreePointCloud::getPoints() const
{
  return points_;
}

std::shared_ptr<std::list<Point>> OctreePointCloud::getPoints(Filter filter) const
{
  std::shared_ptr<std::list<Point>> points(new std::list<Point>());
  
  std::copy_if(points_->begin(), points_->end(), points->begin(), filter);
  
  return points;
}

