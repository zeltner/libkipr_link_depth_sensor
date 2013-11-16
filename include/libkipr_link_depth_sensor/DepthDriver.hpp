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

#include <memory>

/**
 * \file DepthDriver.hpp
 * \brief C++ interface for depth driver used by libkipr_link_depth_sensor
 * \author Stefan Zeltner
 */

#ifndef _DEPTH_DRIVER_HPP_
#define _DEPTH_DRIVER_HPP_

#include "DepthMap.hpp"
#include "DepthMapResolution.h"

namespace libkipr_link_depth_sensor
{
  class DepthDriver
  {
  public:
    static DepthDriver& instance();

    /**
      * Opens the depth driver
      */
    virtual void open() = 0;

    /**
      * Closes the depth driver
      */
    virtual void close() = 0;

    /**
      * Returns the current depth map resolution
      *
      * \return The current resolution
      */
    virtual DepthMapResolution getDepthMapResolution() const = 0;

    /**
      * Sets the DepthMap resolution of new captured depth maps
      *
      * \param resolution The new resolution
      */
    virtual void setDepthMapResolution(DepthMapResolution resolution) = 0;

    /**
      * Returns a Dept Map object containing the current depth values
      *
      * \note The shared_ptr contains a null pointer if there is no depth
      *       map available yet.
      * \return DepthMap object
      */
    virtual std::shared_ptr<DepthMap> getDepthMap() = 0;
  };
}

#endif /* _DEPTH_DRIVER_HPP_ */
