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

namespace libkipr_link_depth_sensor
{
  template <typename T>
  struct Point
  {
    T x;
    T y;
    T z;
    T distance;

    Point(const T& x, const T& y, const T& z, const T& distance)
      : x(x), y(y), z(z), distance(distance) {}
  };
}

#endif /* _POINT_HPP_ */