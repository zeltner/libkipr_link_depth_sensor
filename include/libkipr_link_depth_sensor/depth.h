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

#include "DepthMapResolution.h"

#ifdef __cplusplus
extern "C" {
#endif

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
 * by depth_update.
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
DepthMapResolution get_depth_map_resolution();

/**
 * Set the current depth map resolution.
 *
 * \note Changing the resolution will only affect the next by depth_update
 *       saved depth map.
 * \param resolution New resolution
 * \return 1 on success, 0 otherwise
 * \see depth_update
 * \see get_depth_map_resolution
 */
int set_depth_map_resolution(DepthMapResolution resolution);

/** \} */



/** \name Save depth map
 * Use depth_update()to save the current depth map for future processing.
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
 * You have to call depth_update() before you can access the raw depth
 * measurements.
 *
 * \note All the raw depth functions use a different coordinate system than
 *       the point cloud functions:
 *       x and y are used to address a depth value within of the depth map.
 *       The range of x is between 0 and depth_map_get_width()-1, the range of
 *       y is between 0 and depth_map_get_height()-1.
 *       (0, 0) address the depth value in the upper left corner.
 *
 * \see depth_update
 */
/** \{ */

/**
 * Returns the height of the depth map stored by depth_update in pixel
 *
 * \see depth_update
 *
 * \return Height of the depth map in pixel or 0 if no depth map was saved
 */
int depth_map_get_height();

/**
 * Returns the width of the depth map stored by depth_update in pixel
 *
 * \see depth_update
 *
 * \return Width of the depth map in pixel or 0 if no depth map was saved
 */
int depth_map_get_width();

/**
 * Returns the depth value of the specified point.
 *
 * \see depth_map_get_height
 * \see depth_map_get_width
 *
 * \param x X coordinate of the depth value (depth coordinate system)
 * \param y Y coordinate of the depth value (depth coordinate system)
 * \return The depth value in millimeters or 0 if no depth map was saved or if
 *         the depth value of (x, y) is not visible by the depth sensor
 */
int depth_map_get_depth_at(int x, int y);

/** \} */



/** \name Point cloud functions
 * Use these functions to create a point cloud from a specific depth map region.
 * calling point_cloud_update() is required before any other function can be
 * called.
 *
 * \note All the point cloud functions use a different coordinate system than
 *       the raw depth functions:
 *       x, y and z are used to define a point in a 3D space. The unit is mm.
 *       From camera perspective, the y coordinate increases if an object moves
 *       upwards, the x coordinate increases if it moves from left to right and
 *       the z coordinate increase if it moves straight away from the camera.
 *
 * \see point_cloud_update
 */
/** \{ */

typedef enum PointCloudUpdateFilter_
{
  POINT_CLOUD_FILTER_MIN_X,
  POINT_CLOUD_FILTER_MAX_X,
  POINT_CLOUD_FILTER_MIN_Y,
  POINT_CLOUD_FILTER_MAX_Y,
  POINT_CLOUD_FILTER_MIN_DEPTH,
  POINT_CLOUD_FILTER_MAX_DEPTH,
} PointCloudUpdateFilter;

/**
 * Add a point cloud update filter
 *
 * Add filter to restrict the number of points generated by point_cloud_update().
 * The filter takes effect the next time point_cloud_update() is called.
 * You can add multiple filter like one to restrict the minimum and one to select
 * the maximum depth.
 *
 * \see point_cloud_update
 * \see reset_point_cloud_update_filter
 *
 * \return 1 on success, 0 otherwise
 */
int add_point_cloud_update_filter(PointCloudUpdateFilter filter, int value);

/**
 * Remove all point cloud update filter
 *
 * \see point_cloud_update
 * \see add_point_cloud_update_filter
 *
 * \return 1 on success, 0 otherwise
 */
int reset_point_cloud_update_filter();

/**
 * Save the current point cloud for future processing.
 *
 * \note It is highly recommended to apply a filter before calling
 *       point_cloud_update() as the performance decrease if too many points
 *       are selected.
 *
 * \see add_point_cloud_update_filter
 * \see reset_point_cloud_update_filter
 *
 * \return 1 on success, 0 otherwise
 */
int point_cloud_update();

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
 * Returns the x coordinate of the spicified point
 *
 * \param index The index of the point
 * \return The x coordinate of this point
 * \see number_selected_points
 */
int get_x_of_point(int index);

/**
 * Returns the y coordinate of the spicified point
 *
 * \param index The index of the point
 * \return The y coordinate of this point
 * \see number_selected_points
 */
int get_y_of_point(int index);

/**
 * Returns the z coordinate of the spicified point
 *
 * \param index The index of the point
 * \return The z coordinate of this point
 * \see number_selected_points
 */
int get_z_of_point(int index);

/** \} */

#ifdef __cplusplus
}
#endif

#endif /* _DEPTH_H_ */
