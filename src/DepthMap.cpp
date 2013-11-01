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

#include "libkipr_link_depth_sensor/DepthMap.hpp"

using namespace libkipr_link_depth_sensor;

uint32_t DepthMap::getDistanceAt(uint32_t column, uint32_t row)
{
  throw "Not Implemented!!";
}

uint32_t DepthMap::nColumns()
{
  throw "Not Implemented!!";
}

uint32_t DepthMap::nRows()
{
  throw "Not Implemented!!";
}

void DepthMap::selectSubregion(uint32_t leftmostColumn, uint32_t rightmostColumn,
                               uint32_t uppermostRow, uint32_t lowermostRow)
{
  throw "Not Implemented!!";
}

int DepthMap::selectMinDistance(int max_distance)
{
  throw "Not Implemented!!";
}

void DepthMap::selectMaxDistance(uint32_t min_distance)
{
  throw "Not Implemented!!";
}

void DepthMap::resetSelection()
{
  throw "Not Implemented!!";
}

std::vector<Point<uint32_t> > DepthMap::getPoints()
{
  throw "Not Implemented!!";
}
