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

/**
 * \file depth.h
 * \brief C API of the KIPR Link depth sensor interface
 * \author Stefan Zeltner
 */

#ifndef _DEPTH_H_
#define _DEPTH_H_

#ifdef __cplusplus
extern "C" {
#endif

enum DepthMapResolution
{

};

struct Point
{

};

/**
 * Opens the depth sensor
 * \return 1 on success, 0 otherwise
 */
int depth_open();

/**
 * Closes the depth sensor
 * \return 1 on success, 0 otherwise
 */
int depth_close();

/**
 * Get the current depth map resolution
 * \note Advanced level
 * \return The current depth map resolution
 * \see set_depth_map_resolution
 */
enum DepthMapResolution get_depth_map_resolution();

/**
 * Set the current depth map resolution
 * \note Advanced level
 * \note Changing the resolution will not affect the currently by depth_update
 *       saved depth map
 * \param resolution New resolution
 * \return 1 on success, 0 otherwise
 * \see depth_update
 * \see get_depth_map_resolution
 */
int set_depth_map_resolution(enum DepthMapResolution resolution);

/**
 * Save the current depth map for future processing
 * \return 1 on success, 0 otherwise
 */
int depth_update();

/**
 * Select a row of the current depth map to restrict future processing to
 * that row
 * \param index The index of the selected row
 * \return 1 on success, 0 otherwise
 * \see depth_map_reset_selection
 */
int depth_map_select_row(int index);

/**
 * Select a subregion of the current depth map to restrict future processing to
 * that region
 * \param leftmostColumn Leftmost column of the subregion
 * \param rightmostColumn Rightmost column of the subregion
 * \param uppermostRow Uppermost row of the subregion
 * \param lowermostRow Lowermost row of the subregion
 * \return 1 on success, 0 otherwise
 * \see depth_map_reset_selection
 */
int depth_map_select_subregion(int leftmostColumn,
                               int rightmostColumn,
                               int uppermostRow,
                               int lowermostRow);

/**
 * Resets the selection
 */
void depth_map_reset_selection();

/**
 * Get the distance of the closest point within the selected region
 * \return The distance of the closest point
 * \see depth_map_select_subregion
 * \see depth_map_select_row
 * \see depth_get_closest_point
 */
int depth_get_closest_point_distance();

/**
 * Get the closest point within the selected region
 * \note Advanced level
 * \return The closest point
 * \see depth_map_select_subregion
 * \see depth_map_select_row
 * \see depth_get_closest_point_distance
 */
struct Point depth_get_closest_point();

#ifdef __cplusplus
}
#endif

#endif /* _DEPTH_H_ */
