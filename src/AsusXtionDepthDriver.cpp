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

#include "libkipr_link_depth_sensor/Exception.hpp"
#include "libkipr_link_depth_sensor/AsusXtionDepthDriver.hpp"

using namespace libkipr_link_depth_sensor;
using namespace openni;

AsusXtionDepthDriver& AsusXtionDepthDriver::instance()
{
  static AsusXtionDepthDriver _instance;

  return _instance;
}

void AsusXtionDepthDriver::onDeviceConnected(const DeviceInfo* pInfo)
{
  
}

void AsusXtionDepthDriver::onDeviceDisconnected(const DeviceInfo* pInfo)
{
  
}

void AsusXtionDepthDriver::onDeviceStateChanged(const DeviceInfo* pInfo,
                                                DeviceState state)
{
  
}

AsusXtionDepthDriver::AsusXtionDepthDriver()
{
  Status rc = OpenNI::initialize();
  if(rc != STATUS_OK)
  {
    throw Exception(std::string("Initialize failed with ")
      + OpenNI::getExtendedError());
  }

  OpenNI::addDeviceConnectedListener(this);
  OpenNI::addDeviceDisconnectedListener(this);
  OpenNI::addDeviceStateChangedListener(this);
}

AsusXtionDepthDriver::~AsusXtionDepthDriver()
{
  close();

  OpenNI::removeDeviceConnectedListener(this);
  OpenNI::removeDeviceDisconnectedListener(this);
  OpenNI::removeDeviceStateChangedListener(this);

  OpenNI::shutdown();
}

void AsusXtionDepthDriver::open()
{
  if(!device_.isValid())
  {
    Status rc = device_.open(ANY_DEVICE);
    if(rc != STATUS_OK)
    {
      throw Exception(std::string("Open the device failed with ")
        + OpenNI::getExtendedError());
    }
    device_.open(ANY_DEVICE);

    if(device_.getSensorInfo(SENSOR_DEPTH) != NULL)
    {
      rc = depth_stream_.create(device_, SENSOR_DEPTH);
      if (rc != STATUS_OK)
      {
        device_.close();
        throw Exception(std::string("Create the depth stream failed with ")
          + OpenNI::getExtendedError());
      }
    }
  }
}

void AsusXtionDepthDriver::close()
{
  depth_stream_.stop();
  depth_stream_.destroy();

  device_.close();
}

DepthMapResolution AsusXtionDepthDriver::getDepthMapResolution() const
{
  VideoMode video_mode = depth_stream_.getVideoMode();

  int res_x = video_mode.getResolutionX();
  int res_y = video_mode.getResolutionY();

  if((res_x == 320) && (res_y = 240))
  {
    return DEPTH_MAP_RESOLUTION_320_240;
  }
  else if((res_x == 640) && (res_y = 480))
  {
    return DEPTH_MAP_RESOLUTION_640_480;
  }
  else
  {
    return DEPTH_MAP_INVALID_RESOLUTION;
  }
}

void AsusXtionDepthDriver::setDepthMapResolution(DepthMapResolution resolution)
{
  VideoMode video_mode = depth_stream_.getVideoMode();

  if(DEPTH_MAP_RESOLUTION_320_240)
  {
    video_mode.setResolution(320, 240);
  }
  else if(DEPTH_MAP_RESOLUTION_640_480)
  {
    video_mode.setResolution(640, 480);
  }
  else
  {
    throw Exception(std::string("Invalid resolution"));
  }

  Status rc = depth_stream_.setVideoMode(video_mode);
  if (rc != STATUS_OK)
  {
    throw Exception(std::string("Set the resolution failed with ")
      + OpenNI::getExtendedError());
  }
}

DepthMap AsusXtionDepthDriver::getDepthMap()
{
  throw "Not Implemented!!";
}
