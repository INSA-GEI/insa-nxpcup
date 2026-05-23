#ifndef IMAGE_PROCESSING_USE_CASE_H
#define IMAGE_PROCESSING_USE_CASE_H

/*
Image processing use case for Horizontal Edge Detection.
Makes use of a debug buffer and therefore can only be
defined when `IMAGE_PROCESSING_USE_DEBUG_BUFFER` is truthy
*/

#include "image_processing.h"

#if IMAGE_PROCESSING_USE_DEBUG_BUFFER

#include <stdint.h>
#include <stddef.h>

#include "image_lib/vector2int.h"
#include "image_lib/image_utility.h"
#include "st7796_lcd.h"

/// @brief Compute Horizontal Edge Detection for 1 line and draw feedback on the LCD screen
/// See `g_image_processing_debug_buffer`, `g_image_processing_debug_buffer_dimensions`,
/// `g_image_processing_lcd`, `g_image_processing_line_indices`
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
void image_hed_detect_and_draw_edges(
	ImageConstBuffer image_buffer, Vector2Int image_dimensions_lcd,
	uint16_t x_center, uint16_t y_start, uint16_t y_count, bool lcd_convention,
	uint8_t gradient_threshold128, uint8_t value_threshold128,
	uint16_t* out_gradient_bounds, uint16_t* out_value_bounds);

/// @brief Set this value before calling `image_hed_detect_and_draw_edges` to use this LCD
extern st7796_lcd_t* g_image_processing_lcd;
/// @brief Set this value before calling `image_hed_detect_and_draw_edges` to use these line indices
extern uint16_t* g_image_processing_line_indices;

#endif // IMAGE_PROCESSING_USE_DEBUG_BUFFER

#endif // IMAGE_PROCESSING_USE_CASE_H
