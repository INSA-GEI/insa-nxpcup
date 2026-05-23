#include "image_processing.h"

#include <assert.h>
#include <stdint.h>

#include "image_lib/color_utility.h"
#include "image_lib/image_utility.h"
#include "image_lib/vector2int.h"
#include "image_lib/camera_utility.h"

volatile ImageBuffer g_image_processing_debug_buffer = NULL;
Vector2Int g_image_processing_debug_buffer_dimensions = {0};

uint16_t sum_grayscale64_vertical(ImageConstBuffer image_buffer, uint16_t y_start, uint16_t y_end, uint16_t x)
{
	uint16_t y_sum64 = 0;
	for (uint16_t y = y_start; y < y_end; y++)
	{
		Color16 pixel = image_get_pixel(image_buffer, CAMERA_DIMENSIONS_VERTICAL, vector2int_new(x, y));
		uint16_t grayscale64 = color_rgb_grayscale64(pixel.as_rgb);
		y_sum64 += grayscale64;
	}
	return y_sum64;
}

void image_detect_dark_from_center(
	ImageConstBuffer image_buffer, Vector2Int dimensions,
	uint16_t x_center, uint16_t y_start, uint16_t y_count,
	uint8_t gradient_threshold128, uint8_t value_threshold128,
	uint16_t* out_gradient_bounds, uint16_t* out_value_bounds)
{
	const uint16_t y_end = y_start + y_count;
	const uint16_t equivalent_gradient_threshold = y_count * gradient_threshold128;
	const uint16_t equivalent_value_threshold = y_count * value_threshold128;

	// (x_center -> x_max - 1) then (x_center - 1 -> 0) (assumption that x_max is even)
	int16_t x_offset = 0;
	for (int16_t i_direction = 0; i_direction < 2; i_direction++)
	{
		const int16_t x_direction = 1 - i_direction * 2;
		const uint16_t x_length = (x_direction == 1)
			? (dimensions.x - x_center)
			: x_center;

		const uint16_t x_start = x_center + x_offset;
		uint16_t y_sum64_before = sum_grayscale64_vertical(image_buffer, y_start, y_end, x_start - x_direction);
		uint16_t y_sum64_center = sum_grayscale64_vertical(image_buffer, y_start, y_end, x_start);
		uint16_t y_sum64_after = sum_grayscale64_vertical(image_buffer, y_start, y_end, x_start + x_direction);
		for (uint16_t xi = 0; xi < x_length - 1; xi++)
		{
			assert(0 <= (x_center + (int32_t)x_offset + (int32_t)xi * x_direction));
			assert((x_center + (int32_t)x_offset + (int32_t)xi * x_direction) < dimensions.x);

			const uint16_t x = x_center + x_offset + xi * x_direction;

			// 0 to 128 * y_count
			const int16_t y_sum64_gradient128 = y_sum64_after - y_sum64_before + 64 * y_count;

			// Debug to screen
			if (g_image_processing_debug_buffer != NULL)
			{
				const int16_t y_sum64_sum128 = y_sum64_before + y_sum64_after;
				const uint16_t y_average128 = y_sum64_sum128 / y_count;
				const float average_grayscale = y_average128 / 128.0F;
				const Color16 output_color = color16_rgb_from_float(average_grayscale, average_grayscale, average_grayscale);
				for (uint16_t y = 0; y < g_image_processing_debug_buffer_dimensions.y; y++)
				{
					image_set_pixel(g_image_processing_debug_buffer, g_image_processing_debug_buffer_dimensions, vector2int_new(x, y), output_color);
				}
			}

			if (out_gradient_bounds[i_direction] == UINT16_MAX && y_sum64_gradient128 < equivalent_gradient_threshold)
			{
				out_gradient_bounds[i_direction] = x;
				// Consider breaking since bound was found by gradient criteria
			}

			if (out_value_bounds[i_direction] == UINT16_MAX && y_sum64_center < equivalent_value_threshold)
			{
				out_value_bounds[i_direction] = x;
				// Consider breaking since bound was found by value criteria
			}

			const uint16_t next_xi = xi + 1;
			if (next_xi < x_length - 1)
			{
				const uint16_t next_x = x_center + x_offset + next_xi * x_direction;
				// 0 to 64 * y_count
				y_sum64_before = y_sum64_center;
				y_sum64_center = y_sum64_after;
				y_sum64_after = sum_grayscale64_vertical(image_buffer, y_start, y_end, next_x + x_direction);
			}
		}
		x_offset = -1;
	}
}
