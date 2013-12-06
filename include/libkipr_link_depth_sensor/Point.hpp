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
 * \file Point.hpp
 * \brief This file describes the struct Point
 * \author Stefan Zeltner
 */

#ifndef _POINT_HPP_
#define _POINT_HPP_

#include <stdint.h>

namespace libkipr_link_depth_sensor
{
  struct Point
  {
    int32_t world_x;
    int32_t world_y;
    int32_t world_z;

    int32_t depth_x;
    int32_t depth_y;
    int32_t depth_z;

    uint8_t color_r;
    uint8_t color_g;
    uint8_t color_b;

    Point(int32_t depth_x, int32_t depth_y, int32_t depth_z,
      int32_t world_x, int32_t world_y, int32_t world_z)
      : depth_x(depth_x), depth_y(depth_y), depth_z(depth_z),
        world_x(world_x), world_y(world_y), world_z(world_z),
        color_r(0x00), color_g(0x00), color_b(0x00){}
  };
}

#endif /* _POINT_HPP_ */
