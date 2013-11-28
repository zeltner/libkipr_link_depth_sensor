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

#define N_BINS 34
#define N_LINES 9
#define N_FIXED_SCALE 3150

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
      int x;
      int width = depth_image_get_width();
      int y_center = depth_image_get_height() / 2;
      int depth;
      int max = 0;
      int bucket_size = width / N_BINS;
      int sum = 0;
      int avg[N_BINS];
      int b = 0;
      int cnt = 0;
      
      for(x = 0; x < width; x++)
      {
        depth = get_depth_value(x, y_center);
        if(depth != 0)
        {
          sum += depth;
          cnt++;
        }
        
        if((x % bucket_size) == (bucket_size - 1))
        {
          if(cnt)
          {
            avg[b] = sum / cnt;
          }
          else
          {
            avg[b] = 0;
          }
          
          if(avg[b] > max)
          {
            max = avg[b];
          }
          
          b++;
          sum = 0;
          cnt = 0;
        }
      }
      
#ifdef N_FIXED_SCALE
      max = N_FIXED_SCALE;
#endif
      int step_size = (max/N_LINES)/10;
      int l;
      int step_value;
      
      display_clear();
      for(l = N_LINES; l > 0; l--)
      {
        if(l == N_LINES)
        {
          step_value = max;
        }
        else
        {
          step_value = l * step_size * 10;
        }
        
        if(l & 1)
        {
          printf("%5d | ", step_value);
        }
        else
        {
          printf("      | ");
        }
        
        for(b = 0; b < N_BINS; b++)
        {
          if(avg[b] >= step_value)
          {
            printf("#");
          }
          else
          {
            printf(" ");
          }
        }
        
        printf("\n");
      }
      
      msleep(500);
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
