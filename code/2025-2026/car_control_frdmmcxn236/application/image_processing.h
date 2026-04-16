#ifndef IMAGE_PROCESSING_H
#define IMAGE_PROCESSING_H

#include <stdint.h>
#include <stddef.h>

#include "image_lib/color_utility.h"
#include "image_lib/image_utility.h"
#include "image_lib/vector2int.h"

// Returns from 0 to 64 * (`y_end` - `y_start`)
uint16_t sum_grayscale64_vertical(ImageConstBuffer image_buffer, uint16_t y_start, uint16_t y_end, uint16_t x);

// See `g_image_processing_debug_buffer`, `g_image_processing_debug_buffer_dimensions`
// @param out_gradient_bounds: written to if bound found
// @param out_value_bounds: written to if bound found
void image_detect_dark_from_center(
	ImageConstBuffer image_buffer, Vector2Int dimensions,
	uint16_t x_center, uint16_t y_start, uint16_t y_count,
	uint8_t gradient_threshold128, uint8_t value_threshold128,
	uint16_t* out_gradient_bounds, uint16_t* out_value_bounds);

// Set this value before calling `image_detect_dark_from_center` to draw on this image buffer
extern volatile ImageBuffer g_image_processing_debug_buffer;
// Set this value before calling `image_detect_dark_from_center` to set the image buffer dimensions
extern Vector2Int g_image_processing_debug_buffer_dimensions;

#endif // IMAGE_PROCESSING_H
