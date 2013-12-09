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
 * \file BoundingBox.hpp
 * \brief This file describes the struct BoundingBox
 * \author Stefan Zeltner
 */

#ifndef _BOUNDING_BOX_HPP_
#define _BOUNDING_BOX_HPP_

#include <libkipr_link_depth_sensor/Point.hpp>

namespace libkipr_link_depth_sensor
{
  struct BoundingBox
  {
    Point* min_;
    Point* max_;

    BoundingBox(Point* min, Point* max)
      : min_(min), max_(max) {}

    inline bool contains(const Point* p)
    {
      if(max_ && min_)
      {
        return *p >= *min_ && *p <= *max_;
      }
      else
      {
        return false;
      }
    }

    inline void add(Point* p)
    {
      if(!min_ || p < min_)
      {
        min_ = p;
      }

      if(!max_ || p > max_)
      {
        max_ = p;
      }
    }
  };
}

#endif /* _BOUNDING_BOX_HPP_ */
