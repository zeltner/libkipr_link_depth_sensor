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

// Uncomment this if you mount the depth camera upside down
// #define CAMERA_IS_UPSIDE_DOWN

void printPointCloudInfo()
{
  console_clear();
  printf("Point cloud information\n");
  printf("  - Size: %d\n", points_in_cloud());
  printf("  - Bounding box:\n"
         "    min world coordinate (%d, %d, %d)\n"
         "    max world coordinate (%d, %d, %d)\n\n",
    get_cloud_min_x(), get_cloud_min_y(), get_cloud_min_z(),
    get_cloud_max_x(), get_cloud_max_y(), get_cloud_max_z());
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
  int area_width = 0;
  int area_height = 0;
  
  if(set_depth_camera_resolution(DEPTH_CAMERA_RESOLUTION_640_480) == 0)
  {
    printf("Failed to set the depth camera resolution to 640 x 480\n");
    return 1;
  }
  
#ifdef CAMERA_IS_UPSIDE_DOWN
  if(set_depth_camera_orientation(DEPTH_CAMERA_ORIENTATION_UPSIDE_DOWN) == 0)
  {
    printf("Failed to set the depth camera orientation\n");
    return 1;
  }
#endif
  
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
        
        area_width = depth_image_width / 2;
        area_height = depth_image_height / 2;
      }
      
      // Apply a filter:
      // Divide the image in 4 areas (2x2). If the mouse pointer is over one
      // area, create a filter such that only points within this area are
      // created and displayed.
      
      int mouse_x, mouse_y;
      get_mouse_position(&mouse_x, &mouse_y);
      
      int area_width_offset = (mouse_x / area_width) * area_width;
      int area_height_offset = (mouse_y / area_height) * area_height;
      
      reset_point_cloud_update_filter();
      add_point_cloud_update_filter(POINT_CLOUD_FILTER_MIN_X, area_width_offset);
      add_point_cloud_update_filter(POINT_CLOUD_FILTER_MAX_X,
        area_width_offset + area_width);
      add_point_cloud_update_filter(POINT_CLOUD_FILTER_MIN_Y, area_height_offset);
      add_point_cloud_update_filter(POINT_CLOUD_FILTER_MAX_Y,
        area_height_offset + area_height);
      
      // get point cloud
      if(point_cloud_update())
      {
        printPointCloudInfo();

        // if(color_cloud(POINT_CLOUD_COLOR_MODE_GREY_SCALE))
        // if(color_cloud(POINT_CLOUD_COLOR_MODE_RGB_GRADIENT))
        if(color_cloud(POINT_CLOUD_COLOR_MODE_HUE_GRADIENT))
        {
          for(int y = 0; y < depth_image_height; y++)
          {
            for(int x = 0; x < depth_image_width; x++)
            {
              int red = get_point_color_red(x, y);
              int green = get_point_color_green(x, y);
              int blue = get_point_color_blue(x, y);
              
              graphics_pixel(x, y, red, green, blue);
            }
          }
        }
        else
        {
          printf("Could not color point cloud\n");
        }
      }
      else
      {
        printf("Could not get point cloud\n");
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
