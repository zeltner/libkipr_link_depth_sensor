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

#include <OpenNI.h>

#include "libkipr_link_depth_sensor/Exception.hpp"
#include "libkipr_link_depth_sensor/AsusXtionDepthDriver.hpp"

using namespace libkipr_link_depth_sensor;
using namespace openni;

AsusXtionDepthDriver& AsusXtionDepthDriver::instance()
{
  static AsusXtionDepthDriver _instance;

  return _instance;
}

AsusXtionDepthDriver::AsusXtionDepthDriver()
{
  
}

void AsusXtionDepthDriver::open()
{
  Status rc = OpenNI::initialize();
  if (rc != STATUS_OK)
  {
    throw Exception(std::string("Initialize failed with ") + OpenNI::getExtendedError());
  }
}

void AsusXtionDepthDriver::close()
{
  throw "Not Implemented!!";
}

DepthMapResolution AsusXtionDepthDriver::getDefaultDepthMapResolution() const
{
  throw "Not Implemented!!";
}

DepthMapResolution AsusXtionDepthDriver::getDepthMapResolution() const
{
  throw "Not Implemented!!";
}

void AsusXtionDepthDriver::setDepthMapResolution(DepthMapResolution resolution)
{
  throw "Not Implemented!!";
}

DepthMap AsusXtionDepthDriver::getDepthMap()
{
  throw "Not Implemented!!";
}
