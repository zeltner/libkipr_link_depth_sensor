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
 *
 * This API is keept simple so even unexperienced C programmers are able to use
 * the KIPR Link dept sensor library.
 *
 * Object-oriented programmers should use the C++ API defined in
 * depth.hpp.
 */

#ifndef _DEPTH_H_
#define _DEPTH_H_

#ifdef __cplusplus
extern "C" {
#endif

enum DepthMapResolution
{

};



/** \name Open/Close
 * Use these functions to open / close the depth sensor library in a clean way.
 */
/** \{ */

/**
 * Opens the depth sensor. This is the first function which has to be called
 * before any other function!
 *
 * \return 1 on success, 0 otherwise
 */
int depth_open();

/**
 * Closes the depth sensor
 * \return 1 on success, 0 otherwise
 */
int depth_close();

/** \} */



/** \name Depth map resolution
 * Use these functions to get and set the resolution of the next depth map saved
 * by depth_update for processing.
 *
 * \see depth_update
 */
/** \{ */

/**
 * Get the current depth map resolution.
 *
 * \return The current depth map resolution
 * \see set_depth_map_resolution
 */
enum DepthMapResolution get_depth_map_resolution();

/**
 * Set the current depth map resolution.
 *
 * \note Changing the resolution will not affect the currently by depth_update
 *       saved depth map
 * \param resolution New resolution
 * \return 1 on success, 0 otherwise
 * \see depth_update
 * \see get_depth_map_resolution
 */
int set_depth_map_resolution(enum DepthMapResolution resolution);

/** \} */



/** \name Save depth map
 * Use these functions to save the current depth map for future processing.
 */
/** \{ */

/**
 * Save the current depth map for future processing.
 *
 * \return 1 on success, 0 otherwise
 */
int depth_update();

/** \} */



/** \name Access raw depth measurements
 * Use these functions to retrieve raw depth measurements of the saved depth map.
 *
 * \note Selections have no effect to these functions.
 *
 * \see depth_update
 */
/** \{ */

/**
 * Returns the distance value of the specified point.
 *
 * \param column Column number
 * \param row Row number
 * \return The distance value
 */
int depth_map_get_distance_at(int column, int row);

/** \} */



/** \name Select depth map region
 * Use these functions to select a specific region of the saved depth map and use
 * this region for future processing.
 */
/** \{ */

/**
 * Select a row of the current depth map to restrict future processing to that row.
 *
 * \param index The index of the selected row
 * \return 1 on success, 0 otherwise
 * \see depth_map_reset_selection
 */
int depth_map_select_row(int index);

/**
 * Select a subregion of the current depth map to restrict future processing to
 * that region.
 *
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
 * Select only distances which are equal or bigger than the specified distance
 *
 * \param distance The minimum distance
 * \return 1 on success, 0 otherwise
 * \see depth_map_reset_selection
 */
int depth_map_select_min_distance(int distance);

/**
 * Select only distances which are equal or smaller than the specified distance
 *
 * \param distance The maximum distance
 * \return 1 on success, 0 otherwise
 * \see depth_map_reset_selection
 */
int depth_map_select_max_distance(int distance);

/**
 * Resets the selection.
 */
void depth_map_reset_selection();

/** \} */



/** \name Point operations
 * Use this functions to get a list of points and their attributes
 */
/** \{ */

/**
 * Returns the number of points within the current selected region. The points are
 * enumerated by distance. This means that the distance of point i is equal or
 * less than the distance of i+1.
 *
 * \return The number of points
 */
int number_selected_points();

/**
 * Returns the distance of the spicified point
 *
 * \param index The index of the point
 * \return The distance of this point
 * \see number_selected_points
 */
int distance_of_point(int index);

/**
 * Returns the column index of the spicified point
 *
 * \param index The index of the point
 * \return The column index of this point
 * \see number_selected_points
 */
int column_of_point(int index);

/**
 * Returns the row index of the spicified point
 *
 * \param index The index of the point
 * \return The row index of this point
 * \see number_selected_points
 */
int row_of_point(int index);

/** \} */

#ifdef __cplusplus
}
#endif

#endif /* _DEPTH_H_ */
