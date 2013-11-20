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

#include "libkipr_link_depth_sensor/Exception.hpp"
#include "libkipr_link_depth_sensor/DepthDriver.hpp"
#include "libkipr_link_depth_sensor/depth.h"

namespace libkipr_link_depth_sensor
{
  namespace c_api
  {
    std::shared_ptr<DepthMap> _depth_map;
    std::shared_ptr<PointCloud> _point_cloud;
    
    struct MinMaxFilterValue
    {
    private:
      bool min_is_set;
      int min;
      bool max_is_set;
      int max;
      
    public:
      MinMaxFilterValue()
        : min_is_set(false), max_is_set(false) {}
      
      void setMin(int value)
      {
        min_is_set = true;
        min = value;
      }
      
      void setMax(int value)
      {
        max_is_set = true;
        max = value;
      }
      
      bool filter(int value)
      {
        if(min_is_set && (min > value))
        {
          return false;
        }
        if(max_is_set && (max < value))
        {
          return false;
        }
        
        return true;
      }
    } _filter_x, _filter_y, _filter_depth;
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

    return _depth_map ? 1 : 0;
  }
  catchAllAndReturn(0);
}

int depth_map_get_height()
{
  try
  {
    if(_depth_map)
    {
        return _depth_map->getHeight();
    }
    else
    {
        return 0;
    }
  }
  catchAllAndReturn(0);
}

int depth_map_get_width()
{
  try
  {
    if(_depth_map)
    {
        return _depth_map->getWidth();
    }
    else
    {
        return 0;
    }
  }
  catchAllAndReturn(0);
}

int depth_map_get_depth_at(int x, int y)
{
  try
  {
    if(_depth_map)
    {
        return _depth_map->getDepthAt(x, y);
    }
    else
    {
        throw Exception("Depth map is not valid");
    }
  }
  catchAllAndReturn(0);
}

int add_point_cloud_update_filter(PointCloudUpdateFilter filter, int value)
{
  switch (filter)
  {
  case POINT_CLOUD_FILTER_MIN_X:
    _filter_x.setMin(value);
    return 1;
  case POINT_CLOUD_FILTER_MAX_X:
    _filter_x.setMax(value);
    return 1;
  case POINT_CLOUD_FILTER_MIN_Y:
    _filter_y.setMin(value);
    return 1;
  case POINT_CLOUD_FILTER_MAX_Y:
    _filter_y.setMax(value);
    return 1;
  case POINT_CLOUD_FILTER_MIN_DEPTH:
    _filter_depth.setMin(value);
    return 1;
  case POINT_CLOUD_FILTER_MAX_DEPTH:
    _filter_depth.setMax(value);
    return 1;
    
  default:
    return 0;
  }
}

int reset_point_cloud_update_filter()
{
  _filter_x = MinMaxFilterValue();
  _filter_y = MinMaxFilterValue();
  _filter_depth = MinMaxFilterValue();
  
  return 1;
}

int point_cloud_update()
{
  try
  {
    if(_depth_map)
    {
      _point_cloud = _depth_map->getPointCloud(
        [](const DepthMap* _this, int x, int y, int& depth) -> bool
        {
          return _filter_x.filter(x) && _filter_y.filter(y)
            && _filter_depth.filter(depth);
        });

      return _point_cloud ? 1 : 0;
    }
    else
    {
        throw Exception("Depth map is not valid");
    }
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
