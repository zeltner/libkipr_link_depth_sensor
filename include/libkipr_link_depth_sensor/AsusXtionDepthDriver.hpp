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

/**
 * \file DepthDriver.hpp
 * \brief C++ interface for depth driver used by libkipr_link_depth_sensor
 * \author Stefan Zeltner
 */

#ifndef _ASUS_XTION_DEPTH_DRIVER_HPP_
#define _ASUS_XTION_DEPTH_DRIVER_HPP_

#include "DepthDriver.hpp"

namespace libkipr_link_depth_sensor
{
  class AsusXtionDepthDriver : public DepthDriver,
                               public openni::OpenNI::DeviceConnectedListener,
                               public openni::OpenNI::DeviceDisconnectedListener,
                               public openni::OpenNI::DeviceStateChangedListener
  {
  public:
    static AsusXtionDepthDriver& instance();

    /**
      * Opens the ASUS Xtion depth driver
      */
    void open();

    /**
      * Closes the ASUS Xtion depth driver
      */
    void close();

    /**
      * Returns the current depth map resolution
      *
      * \return The current resolution
      */
    DepthMapResolution getDepthMapResolution() const;

    /**
      * Sets the DepthMap resolution of new captured depth maps
      *
      * \param resolution The new resolution
      */
    void setDepthMapResolution(DepthMapResolution resolution);

    /**
      * Returns a Dept Map object containing the current depth values
      *
      * \return DepthMap object
      */
    DepthMap getDepthMap();

    ~AsusXtionDepthDriver();

  private:
    openni::Device device_;
    openni::VideoStream depth_stream_;

    // AsusXtionDepthDriver is a singleton
    AsusXtionDepthDriver();
    AsusXtionDepthDriver(AsusXtionDepthDriver const&);
    void operator=(AsusXtionDepthDriver const&);

    // Implement OpenNI::DeviceConnectedListener::onDeviceConnected()
    virtual void onDeviceConnected(const openni::DeviceInfo* pInfo);

    // Implement OpenNI::DeviceDisconnectedListener::onDeviceDisconnected()
    virtual void onDeviceDisconnected(const openni::DeviceInfo* pInfo);

    // Implement OpenNI::DeviceStateChangedListener::onDeviceStateChanged()
    virtual void onDeviceStateChanged(const openni::DeviceInfo* pInfo, openni::DeviceState state);
  };
}

#endif /* _ASUS_XTION_DEPTH_DRIVER_HPP_ */
