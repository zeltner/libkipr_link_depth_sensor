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
 * \file DepthMap.hpp
 * \brief This file describes the class DepthMap
 * \author Stefan Zeltner
 */

#ifndef _DEPTH_MAP_HPP_
#define _DEPTH_MAP_HPP_

#include <stdint.h>

namespace libkipr_link_depth_sensor
{
  class DepthMap
  {
  public:
    /**
    * Returns the number of rows
    *
    * \return The number of rows
    */
    uint32_t nRows();

    /**
    * Returns the number of columns
    *
    * \return The number of columns
    */
    uint32_t nColumns();

    /**
    * Returns the distance value of the specified point.
    *
    * \param column Column number
    * \param row Row number
    * \return The distance value
    */
    uint32_t getDistanceAt(uint32_t column, uint32_t row);

    /**
    * Select a subregion of the current depth map to restrict future processing to
    * that region.
    *
    * \param leftmostColumn Leftmost column of the subregion
    * \param rightmostColumn Rightmost column of the subregion
    * \param uppermostRow Uppermost row of the subregion
    * \param lowermostRow Lowermost row of the subregion
    */
    void select(uint32_t leftmostColumn, uint32_t rightmostColumn,
                uint32_t uppermostRow, uint32_t lowermostRow);
  };
}

#endif /* _DEPTH_MAP_HPP_ */
