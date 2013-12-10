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

#include <stdlib.h>

#define SHOW_DEPTH_UNDER_MOUSE

void HSVtoRGB(int hue, int* r, int* g, int* b)
{
  // http://en.wikipedia.org/wiki/HSV_color_space#From_HSV
  // s = 1.0
  // v = 1.0
  // c = 1.0
  // m = 0

  int h = hue/60;

  int x = 0xFF - abs(h % (2*0xFF) - 0xFF);

  if(h < (1*0xFF))
  {
    *r = 0xFF;
    *g = x;
    *b = 0;
  }
  else if(h < (2*0xFF))
  {
    *r = x;
    *g = 0xFF;
    *b = 0;
  }
  else if(h < (3*0xFF))
  {
    *r = 0;
    *g = 0xFF;
    *b = x;
  }
  else if(h < (4*0xFF))
  {
    *r = 0;
    *g = x;
    *b = 0xFF;
  }
  else if(h < (5*0xFF))
  {
    *r = x;
    *g = 0;
    *b = 0xFF;
  }
  else
  {
    *r = 0xFF;
    *g = 0;
    *b = x;
  }
}

int main(int argc, char** argv)
{
  if(!depth_open())
  {
    printf("Unable to open libkipr_link_depth_sensor\n");
    return 1;
  }

  int depth_image_height = -1;
  int depth_image_width = -1;

  int mouse_x;
  int mouse_y;

  int last_max_depth = 6000 /* mm */;
  int max_depth;

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

      get_mouse_position(&mouse_x, &mouse_y);
      max_depth = 0;

      // display depth image
      for(int y = 0; y < depth_image_height; y++)
      {
        for(int x = 0; x < depth_image_width; x++)
        {
          int depth = get_depth_value(x, y);

          // save max depth
          if(depth > max_depth)
          {
            max_depth = depth;
          }

          // color invalid depth pixel red
          if(depth && last_max_depth)
          {
            int r;
            int g;
            int b;

            HSVtoRGB(360*0xFF*depth/last_max_depth, &r, &g, &b);

            graphics_pixel(x, y, r, g, b);
          }
          else
          {
            graphics_pixel(x, y, 0xFF, 0xFF, 0xFF);
          }

          #ifdef SHOW_DEPTH_UNDER_MOUSE
            if(mouse_x == x && mouse_y == y)
            {
              console_clear();
              printf("depth at (%d, %d) is %d mm\n", x, y, depth);
            }
          #endif
        }
      }

      last_max_depth = max_depth;

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
