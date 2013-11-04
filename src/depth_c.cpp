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

#include <iostream>
#include <exception>

#include "libkipr_link_depth_sensor/DepthDriver.hpp"
#include "libkipr_link_depth_sensor/depth.h"

namespace libkipr_link_depth_sensor
{
  namespace c_api
  {
    DepthMap _depthMap;

    std::vector<Point<uint32_t> > _points;
  }
}

using namespace libkipr_link_depth_sensor;
using namespace libkipr_link_depth_sensor::c_api;

#define catchAllAndReturnOnError(return_value) \
  catch(std::exception& e) { std::cerr << e.what() << std::endl; } \
  catch(...) {} \
  return (return_value)

int depth_open()
{
  try
  {
    DepthDriver::instance().open();

    return 1;
  }
  catchAllAndReturnOnError(0);
}

int depth_close()
{
  try
  {
    DepthDriver::instance().close();

    return 1;
  }
  catchAllAndReturnOnError(0);
}

DepthMapResolution get_depth_map_resolution()
{
  try
  {
    return DepthDriver::instance().getDepthMapResolution();
  }
  catchAllAndReturnOnError(DEPTH_MAP_INVALID_RESOLUTION);
}

int set_depth_map_resolution(DepthMapResolution resolution)
{
  try
  {
    DepthDriver::instance().setDepthMapResolution(resolution);

    return 1;
  }
  catchAllAndReturnOnError(0);
}

int depth_update()
{
  try
  {
    _depthMap = DepthDriver::instance().getDepthMap();

    return 1;
  }
  catchAllAndReturnOnError(0);
}

int depth_map_get_distance_at(int column, int row)
{
  try
  {
    return _depthMap.getDistanceAt(column, row);
  }
  catchAllAndReturnOnError(0);
}

int depth_map_select_row(int index)
{
  try
  {
    return depth_map_select_subregion(0, _depthMap.nColumns() - 1, index, index);
  }
  catchAllAndReturnOnError(0);
}

int depth_map_select_subregion(int leftmostColumn,
                               int rightmostColumn,
                               int uppermostRow,
                               int lowermostRow)
{
  try
  {
    _depthMap.selectSubregion(leftmostColumn, rightmostColumn, uppermostRow, lowermostRow);

    return 1;
  }
  catchAllAndReturnOnError(0);
}

int depth_map_select_min_distance(int distance)
{
  try
  {
    _depthMap.selectMaxDistance(distance);

    return 1;
  }
  catchAllAndReturnOnError(0);
}

int depth_map_select_max_distance(int distance)
{
  try
  {
    _depthMap.selectMinDistance(distance);

    return 1;
  }
  catchAllAndReturnOnError(0);
}

int depth_map_reset_selection()
{
  try
  {
    _depthMap.resetSelection();

    return 1;
  }
  catchAllAndReturnOnError(0);
}

int number_selected_points()
{
  try
  {
    _points = _depthMap.getPoints();

    return _points.size();
  }
  catchAllAndReturnOnError(0);
}

int distance_of_point(int index)
{
  try
  {
    return _points[index].distance;
  }
  catchAllAndReturnOnError(0);
}

int get_x_of_point(int index)
{
  try
  {
    return _points[index].x;
  }
  catchAllAndReturnOnError(0);
}

int get_y_of_point(int index)
{
  try
  {
    return _points[index].y;
  }
  catchAllAndReturnOnError(0);
}

int get_z_of_point(int index)
{
  try
  {
    return _points[index].z;
  }
  catchAllAndReturnOnError(0);
}
