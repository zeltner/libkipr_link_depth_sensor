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

int main(int argc, char** argv)
{
  if(!depth_open())
  {
    printf("Unable to open libkipr_link_depth_sensor\n");
    return 1;
  }
  
  int depth_image_height = -1;
  int depth_image_width = -1;
  
  if(set_depth_camera_resolution(DEPTH_CAMERA_RESOLUTION_640_480) == 0)
  {
    printf("Failed to set the depth camera resolution to 640 x 480\n");
    return 1;
  }
  
  printf("Press 'Q' to stop\n");
  
  while(!get_key_state('Q'))
  {
    if(depth_update())
    {
      if(depth_image_height == -1)
      {
        // initialize the graphics output
        depth_image_height = depth_image_get_height();
        depth_image_width = depth_image_get_width();
        
        graphics_open(depth_image_width, depth_image_height);
      }
      
      // display depth image
      for(int y = 0; y < depth_image_height; y++)
      {
        for(int x = 0; x < depth_image_width; x++)
        {
          int depth = get_depth_value(x, y);
          
          // max depth is 2 meter
          if(depth > 2000)
          {
            depth = 2000;
          }
          
          // color invalid depth pixel red
          if(depth)
          {
            int color = 0xFF*depth/2000;
            graphics_pixel(x, y, color, color, color);
          }
          else
          {
            graphics_pixel(x, y, 0xFF, 0x00, 0x00);
          }
        }
      }
	  
	  graphics_update();
    }
    else
    {
      printf("No depth image received yet\n");
      msleep(2000);
    }
  }
  
  graphics_close();
  depth_close();

  return 0;
}
