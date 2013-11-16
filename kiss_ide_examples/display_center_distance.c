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
  
  printf("Press the 'A' button for three seconds to stop\n");
  
  while(a_button() == 0)
  {
    if(depth_update())
    {
      int x_center = depth_map_get_width() / 2;
      int y_center = depth_map_get_height() / 2;
      int depth_center = depth_map_get_distance_at(x_center, y_center);
      
      printf("Depth at(%d, %d) is %d\n", x_center, y_center, depth_center);
      msleep(2000);
    }
    else
    {
      printf("No depth frame received yet\n");
      msleep(2000);
    }
  }
  
  depth_close();

  return 0;
}
