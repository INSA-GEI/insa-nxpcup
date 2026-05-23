#include <stdint.h>
#include <stddef.h>

#include "image_processing_use_case.h"
#include "image_lib/vector2int.h"
#include "image_lib/image_utility.h"
#include "image_lib/camera_utility.h"
#include "image_lib/lcd_utility.h"

#include "fsl_common.h"

#if IMAGE_PROCESSING_USE_DEBUG_BUFFER
st7796_lcd_t* g_image_processing_lcd = NULL;
uint16_t* g_image_processing_line_indices = NULL;

void image_hed_detect_and_draw_edges(
	ImageConstBuffer image_buffer, Vector2Int image_dimensions_lcd,
	uint16_t x_center, uint16_t y_start, uint16_t y_count, bool lcd_convention,
	uint8_t gradient_threshold128, uint8_t value_threshold128,
	uint16_t* out_gradient_bounds, uint16_t* out_value_bounds)
{
	image_hed_detect_dark_from_center(image_buffer, image_dimensions_lcd,
		x_center, y_start, y_count, lcd_convention,
		gradient_threshold128, value_threshold128,
		out_gradient_bounds, out_value_bounds
	);

	const Vector2Int debug_buffer_dimensions = g_image_processing_debug_buffer_dimensions;

	const Vector2Int long_rectangle_dimensions = vector2int_new(debug_buffer_dimensions.x / 2, 1);
	//const Vector2Int wide_rectangle_dimensions = vector2int_new(debug_buffer_dimensions.x / 4, 3);
	//const uint16_t wide_rectangle_x_offset = debug_buffer_dimensions.x / 8;
	for (uint16_t i = 0; i < ARRAY_SIZE(out_gradient_bounds); i++)
	{
		if (out_gradient_bounds[i] != UINT16_MAX)
		{
			const Color16 gradient_color = (i == 0) ? COLOR_RGB_ORANGE : COLOR_RGB_CYAN;
			const Vector2Int location = vector2int_new(0, out_gradient_bounds[i]);
			image_fill_rectangle(g_image_processing_debug_buffer, debug_buffer_dimensions, location, long_rectangle_dimensions, gradient_color);
			//const Vector2Int wide_location = vector2int_new(location.x + wide_rectangle_x_offset, location.y - 1);
			//image_fill_rectangle(g_image_processing_debug_buffer, debug_buffer_dimensions, wide_location, wide_rectangle_dimensions, gradient_color);
		}
		/* else */ if (out_value_bounds[i] != UINT16_MAX)
		{
			const Color16 value_color = (i == 0) ? color16_rgb_from_float(0, 0.8F, 0) : COLOR_RGB_MAGENTA;
			const Vector2Int location = vector2int_new(debug_buffer_dimensions.x / 2, out_value_bounds[i]);
			image_fill_rectangle(g_image_processing_debug_buffer, debug_buffer_dimensions, location, long_rectangle_dimensions, value_color);
			//const Vector2Int wide_location = vector2int_new(location.x + wide_rectangle_x_offset, location.y - 1);
			//image_fill_rectangle(g_image_processing_debug_buffer, debug_buffer_dimensions, wide_location, wide_rectangle_dimensions, value_color);
		}
	}

	const uint16_t centering_offset = debug_buffer_dimensions.x / 2;
	const uint16_t y_start_global = g_image_processing_line_indices[y_start];
	lcd_utility_load_ranges(g_image_processing_lcd, g_image_processing_debug_buffer, debug_buffer_dimensions,
		index_range_with_length(LCD_WIDTH / 2 + y_start_global - centering_offset, debug_buffer_dimensions.x),
		index_range_with_length(0, debug_buffer_dimensions.y)
	);
}

#endif // IMAGE_PROCESSING_USE_DEBUG_BUFFER
