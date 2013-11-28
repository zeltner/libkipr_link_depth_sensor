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

void pullDepthImage()
{
  printf("Pulling a depth image\n");
  while(!depth_update())
  {
      msleep(2000);
  }
}

void showResolution()
{  
  if(get_depth_camera_resolution() == DEPTH_CAMERA_RESOLUTION_320_240)
  {
    printf("Current camera resolution: 320 x 240\n");
  }
  else if(get_depth_camera_resolution() == DEPTH_CAMERA_RESOLUTION_640_480)
  {
    printf("Current camera resolution: 640 x 480\n");
  }
  else
  {
     printf("Unknown camera resolution\n");
  }
  
  printf("Pulled image resolution %d x %d\n",
    depth_image_get_width(), depth_image_get_height());
}

int main(int argc, char** argv)
{
  if(!depth_open())
  {
    printf("Unable to open libkipr_link_depth_sensor\n");
    return 1;
  }
  
  pullDepthImage();
  showResolution();
  
  printf("\nSet camera resolution to 320 x 240\n");
  if(set_depth_camera_resolution(DEPTH_CAMERA_RESOLUTION_320_240) == 0)
  {
    printf("Failed to set the camera resolution to 320 x 240\n");
  }
  
  pullDepthImage();
  showResolution();
  
  printf("\nSet camera resolution to 640 x 480\n");
  if(set_depth_camera_resolution(DEPTH_CAMERA_RESOLUTION_640_480) == 0)
  {
    printf("Failed to set the depth camera resolution to 640 x 480\n");
  }
  
  showResolution();
  printf("\nNote: The pulled depth image shows still the old resolution because "
    "we didn't call depth_update() yet\n\n");
  
  pullDepthImage();
  showResolution();
  
  depth_close();

  return 0;
}
