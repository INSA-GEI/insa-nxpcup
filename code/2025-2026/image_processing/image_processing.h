#ifndef IMAGE_PROCESSING_H
#define IMAGE_PROCESSING_H

/*
Image processing implementations of Horizontal Edge Detection
(the main focus is `image_hed_detect_dark_from_center`) with defensive
copying of the selected lines before computation (`image_hed_copy_lines`)

NOTE: What we call the lcd convention is considering that right and up (x and y)
are in portrait mode when looking at the lcd (when reading the NXP logo)
*/

#define IMAGE_PROCESSING_USE_DEBUG_BUFFER 1

#include <stdint.h>
#include <stddef.h>

#include "image_lib/color_utility.h"
#include "image_lib/image_utility.h"
#include "image_lib/vector2int.h"

/// @brief Sum the grayscale value of a line of pixels in
/// `image_buffer` from (`x`, `y_start`) to (`x`, `y_end`)
/// (using `color_rgb_grayscale64`)
/// @param image_buffer 
/// @param image_dimensions_lcd The dimensions of `image_buffer` in lcd convention
/// @param lcd_convention Whether coordinates (`x`, `y_start`, `y_end`)
/// are specified in the lcd convention
/// @returns A value from 0 to 64 * (`y_end` - `y_start`)
uint16_t image_sum_grayscale64_vertical(
	ImageConstBuffer image_buffer, Vector2Int image_dimensions_lcd,
	uint16_t y_start, uint16_t y_end, uint16_t x, bool lcd_convention);

/// Core of Horizontal Edge Detection: detects dark edges in `image_buffer` along the
/// x direction and writes them in `out_gradient_bounds` and `out_value_bounds`.
/// See `g_image_processing_debug_buffer`, `g_image_processing_debug_buffer_dimensions`
/// @param image_buffer 
/// @param image_dimensions_lcd The dimensions of `image_buffer` in lcd convention
/// @param x_center The abscissa to start searching edges from
/// @param y_start The ordinate of the line to search along
/// @param y_count The number of contiguous lines to search in ordinate
/// @param lcd_convention Whether coordinates (`x_center`, `y_start`, `y_count`)
/// are specified in the lcd convention
/// @param gradient_threshold128 The threshold under which gradient values are considered edges
/// (representated between 0 and 128)
/// @param value_threshold128 The threshold under which grayscale values are considered edges
/// (representated between 0 and 128)
/// @param out_gradient_bounds Must have at least 2 elements, written to only if bound found
/// @param out_value_bounds Must have at least 2 elements, written to only if bound found
void image_hed_detect_dark_from_center(
	ImageConstBuffer image_buffer, Vector2Int image_dimensions_lcd,
	uint16_t x_center, uint16_t y_start, uint16_t y_count, bool lcd_convention,
	uint8_t gradient_threshold128, uint8_t value_threshold128,
	uint16_t* out_gradient_bounds, uint16_t* out_value_bounds);

/// @brief Copy lines from `image_buffer` with `dimensions` at `indices`
/// along `axis` in `line_direction` to `out_buffer`.
/// Each lines' n-th pixel is sequentially copied to `out_buffer` for n along `axis` in `line_direction`.
/// In the case where `image_buffer` is being progressively written to as the copying happens, this
/// allows to save the first pixels that will be overwritten (this depends on orientation and direction).
/// @param image_buffer 
/// @param image_dimensions 
/// @param line_indices 
/// @param line_count 
/// @param axis Line axis
/// @param line_direction Direction of the copy: 1 for increasing, -1 for decreasing
/// @param out_buffer Must have size of at least `image_dimensions[axis]` * `index_count`.
/// Lines are stored contiguously though copied one pixel each at a time
void image_hed_copy_lines(
	ImageConstBuffer image_buffer, Vector2Int image_dimensions,
	const uint16_t* line_indices, uint16_t line_count,
	Axis axis, int8_t line_direction, Color16* out_buffer);

/// @brief Computes the next search center from the result of a call to `image_hed_detect_dark_from_center`.
/// @param gradient_bounds Array of at least 2 `uint16_t` with values resulting
/// from a call to `image_hed_detect_dark_from_center`
/// @param value_bounds Array of at least 2 `uint16_t` with values resulting
/// from a call to `image_hed_detect_dark_from_center`
/// @param range_length The max value of bounds (image width if searching horizontally, image height if searching vertically)
/// @return The average of bounds given by `gradient_bounds` in priority, else by `value_bounds`,
/// while handling missing detections
uint16_t image_hed_next_search_center(const uint16_t* gradient_bounds, const uint16_t* value_bounds, uint16_t range_length);

#if IMAGE_PROCESSING_USE_DEBUG_BUFFER
// Set this value before calling `image_hed_detect_dark_from_center` to draw on this image buffer
extern volatile ImageBuffer g_image_processing_debug_buffer;
// Set this value before calling `image_hed_detect_dark_from_center` to set the image buffer dimensions
extern Vector2Int g_image_processing_debug_buffer_dimensions;
#endif

#endif // IMAGE_PROCESSING_H
