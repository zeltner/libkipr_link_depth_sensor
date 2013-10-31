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

#include "DepthDriver.hpp"

#include "depth.h"

namespace libkipr_link_depth_sensor
{
  namespace c_api
  {
    DepthMap _depthMap;
  }
}

using namespace libkipr_link_depth_sensor;
using namespace libkipr_link_depth_sensor::c_api;

int depth_open()
{
  try
  {
    DepthDriver::instance().open();

    return 1;
  }
  catch(...)
  {
    return 0;
  }
}

int depth_close()
{
  try
  {
    DepthDriver::instance().close();

    return 1;
  }
  catch(...)
  {
    return 0;
  }
}

DepthMapResolution get_default_depth_map_resolution()
{
  try
  {
    return DepthDriver::instance().getDefaultDepthMapResolution();
  }
  catch(...)
  {
    return DEPTH_MAP_INVALID_RESOLUTION;
  }
}

DepthMapResolution get_depth_map_resolution()
{
  try
  {
    return DepthDriver::instance().getDepthMapResolution();
  }
  catch(...)
  {
    return DEPTH_MAP_INVALID_RESOLUTION;
  }
}

int set_depth_map_resolution(DepthMapResolution resolution)
{
  try
  {
    DepthDriver::instance().setDepthMapResolution(resolution);

    return 1;
  }
  catch(...)
  {
    return 0;
  }
}

int depth_update()
{
  try
  {
    _depthMap = DepthDriver::instance().getDepthMap();

    return 1;
  }
  catch(...)
  {
    return 0;
  }
}
