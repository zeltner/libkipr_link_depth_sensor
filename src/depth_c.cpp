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
#include <memory>

#include "libkipr_link_depth_sensor/DepthDriver.hpp"
#include "libkipr_link_depth_sensor/depth.h"

namespace libkipr_link_depth_sensor
{
  namespace c_api
  {
    std::shared_ptr<DepthMap> _depth_map;
  }
}

using namespace libkipr_link_depth_sensor;
using namespace libkipr_link_depth_sensor::c_api;

#define catchAllAndReturn(return_value) \
  catch(std::exception& e) { std::cerr << e.what() << std::endl; } \
  catch(const char* msg) { std::cerr << msg << std::endl; } \
  catch(...) {} \
  return (return_value)

int depth_open()
{
  try
  {
    DepthDriver::instance().open();

    return 1;
  }
  catchAllAndReturn(0);
}

int depth_close()
{
  try
  {
    DepthDriver::instance().close();

    return 1;
  }
  catchAllAndReturn(0);
}

DepthMapResolution get_depth_map_resolution()
{
  try
  {
    return DepthDriver::instance().getDepthMapResolution();
  }
  catchAllAndReturn(DEPTH_MAP_INVALID_RESOLUTION);
}

int set_depth_map_resolution(DepthMapResolution resolution)
{
  try
  {
    DepthDriver::instance().setDepthMapResolution(resolution);

    return 1;
  }
  catchAllAndReturn(0);
}

int depth_update()
{
  try
  {
    _depth_map = DepthDriver::instance().getDepthMap();

    return 1;
  }
  catchAllAndReturn(0);
}

int depth_map_get_distance_at(int column, int row)
{
  try
  {
    return _depth_map->getDistanceAt(column, row);
  }
  catchAllAndReturn(0);
}

int depth_map_select_row(int index)
{
  try
  {
    throw "Not Implemented!!";
  }
  catchAllAndReturn(0);
}

int depth_map_select_subregion(int leftmostColumn,
                               int rightmostColumn,
                               int uppermostRow,
                               int lowermostRow)
{
  try
  {
    throw "Not Implemented!!";
  }
  catchAllAndReturn(0);
}

int depth_map_select_min_distance(int distance)
{
  try
  {
    throw "Not Implemented!!";
  }
  catchAllAndReturn(0);
}

int depth_map_select_max_distance(int distance)
{
  try
  {
    throw "Not Implemented!!";
  }
  catchAllAndReturn(0);
}

int depth_map_reset_selection()
{
  try
  {
    throw "Not Implemented!!";
  }
  catchAllAndReturn(0);
}

int number_selected_points()
{
  try
  {
    throw "Not Implemented!!";
  }
  catchAllAndReturn(0);
}

int distance_of_point(int index)
{
  try
  {
    throw "Not Implemented!!";
  }
  catchAllAndReturn(0);
}

int get_x_of_point(int index)
{
  try
  {
    throw "Not Implemented!!";
  }
  catchAllAndReturn(0);
}

int get_y_of_point(int index)
{
  try
  {
    throw "Not Implemented!!";
  }
  catchAllAndReturn(0);
}

int get_z_of_point(int index)
{
  try
  {
    throw "Not Implemented!!";
  }
  catchAllAndReturn(0);
}
