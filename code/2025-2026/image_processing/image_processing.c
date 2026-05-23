#include "image_processing.h"

#include <assert.h>
#include <stdbool.h>
#include <stdint.h>

#include "image_lib/color_utility.h"
#include "image_lib/image_utility.h"
#include "image_lib/vector2int.h"
#include "image_lib/camera_utility.h"

#if IMAGE_PROCESSING_USE_DEBUG_BUFFER
volatile ImageBuffer g_image_processing_debug_buffer = NULL;
Vector2Int g_image_processing_debug_buffer_dimensions = {0};
#endif // IMAGE_PROCESSING_USE_DEBUG_BUFFER

uint16_t image_sum_grayscale64_vertical(
	ImageConstBuffer image_buffer, Vector2Int image_dimensions_lcd,
	uint16_t y_start, uint16_t y_end, uint16_t x, bool lcd_convention)
{
	uint16_t y_sum64 = 0;
	for (uint16_t y = y_start; y < y_end; y++)
	{
		Vector2Int location = vector2int_new(x, y);
		if (!lcd_convention)
			location = vector2int_swap(location);
		Color16 pixel = image_get_pixel(image_buffer, image_dimensions_lcd, location);
		uint16_t grayscale64 = color_rgb_grayscale64(pixel.as_rgb);
		y_sum64 += grayscale64;
	}
	return y_sum64;
}

void image_hed_detect_dark_from_center(
	ImageConstBuffer image_buffer, Vector2Int image_dimensions_lcd,
	uint16_t x_center, uint16_t y_start, uint16_t y_count, bool lcd_convention,
	uint8_t gradient_threshold128, uint8_t value_threshold128,
	uint16_t* out_gradient_bounds, uint16_t* out_value_bounds)
{
	const uint16_t y_end = y_start + y_count;
	const uint16_t equivalent_gradient_threshold = y_count * gradient_threshold128;
	const uint16_t equivalent_value_threshold = y_count * value_threshold128;
	const Axis horizontal = lcd_convention ? AXIS_X : AXIS_Y;
	const Axis vertical = lcd_convention ? AXIS_Y : AXIS_X;
	const uint16_t image_width = vector2int_get(image_dimensions_lcd, horizontal);
	const uint16_t image_height = vector2int_get(image_dimensions_lcd, vertical);

    assert(x_center < image_width); // X center is in the image
    assert(y_start < image_height); // Y start is in the image
    assert(y_start + y_count <= image_height); // Y end is in the image

    // Clamp x_center in valid bound (+-1 from edges)
    if (x_center == 0)
    {
        x_center = 1;
    }
    else if (x_center == image_width)
    {
        x_center = image_width - 1;
    }

	// (x_center -> x_max - 1) then (x_center - 1 -> 0)
	int16_t x_offset = 0;
	for (uint16_t i_direction = 0; i_direction < 2; i_direction++)
	{
		const int16_t x_direction = (i_direction == 0) ? 1 : -1;
		const uint16_t x_length = (i_direction == 0)
			? (image_width - x_center)
			: x_center;

        const uint16_t x_start = x_center + x_offset;
        if (x_start == 0)
            break;
        const int32_t x_before = (int32_t)x_start - (int32_t)x_direction;
        const int32_t x_after = (int32_t)x_start + (int32_t)x_direction;
        if (x_before < 0 || image_width <= x_after) // Not enough space to process
            break;

		uint16_t y_sum64_before = image_sum_grayscale64_vertical(image_buffer, image_dimensions_lcd, y_start, y_end, x_before, lcd_convention);
		uint16_t y_sum64_center = image_sum_grayscale64_vertical(image_buffer, image_dimensions_lcd, y_start, y_end, x_start, lcd_convention);
		uint16_t y_sum64_after = image_sum_grayscale64_vertical(image_buffer, image_dimensions_lcd, y_start, y_end, x_after, lcd_convention);
		const uint16_t xi_upper_bound = x_length - 1;
		for (uint16_t xi = 0; xi < xi_upper_bound; xi++)
		{
			assert(0 <= (x_center + (int32_t)x_offset + (int32_t)xi * x_direction));
			assert((x_center + (int32_t)x_offset + (int32_t)xi * x_direction) < image_width);

			const uint16_t x = x_start + xi * x_direction;

			// 0 to 128 * y_count
			const int16_t y_sum64_gradient128 = y_sum64_after - y_sum64_before + 64 * y_count;

#if IMAGE_PROCESSING_USE_DEBUG_BUFFER
			// Debug to screen
			if (g_image_processing_debug_buffer != NULL)
			{
				const uint16_t debug_buffer_width = vector2int_get(g_image_processing_debug_buffer_dimensions, horizontal);
				const uint16_t debug_buffer_height = vector2int_get(g_image_processing_debug_buffer_dimensions, vertical);

				const int16_t y_sum64_sum128 = y_sum64_before + y_sum64_after;
				const uint16_t y_average128 = y_sum64_sum128 / y_count;
				const float average_grayscale = y_average128 / 128.0F;
				const Color16 output_color = color16_rgb_from_float(average_grayscale, average_grayscale, average_grayscale);
				for (uint16_t y = 0; y < debug_buffer_height; y++)
				{
					Vector2Int location = vector2int_new(x, y);
					if (!lcd_convention)
						location = vector2int_swap(location);
					image_set_pixel(g_image_processing_debug_buffer, g_image_processing_debug_buffer_dimensions, location, output_color);
				}
			}
#endif

			if (out_gradient_bounds[i_direction] == UINT16_MAX && y_sum64_gradient128 < equivalent_gradient_threshold)
			{
				out_gradient_bounds[i_direction] = x;
				// Consider breaking since bound was found by gradient criteria

				if (out_value_bounds[i_direction] != UINT16_MAX)
				{
					// break;
					// Nothing left to search
				}
			}

			if (out_value_bounds[i_direction] == UINT16_MAX && y_sum64_center < equivalent_value_threshold)
			{
				out_value_bounds[i_direction] = x;
				// Consider breaking since bound was found by value criteria

				if (out_gradient_bounds[i_direction] != UINT16_MAX)
				{
					// break;
					// Nothing left to search
				}
			}

			const uint16_t next_xi = xi + 1;
			if (next_xi < xi_upper_bound)
			{
				const uint16_t next_x = x_start + next_xi * x_direction;
				// 0 to 64 * y_count
				y_sum64_before = y_sum64_center;
				y_sum64_center = y_sum64_after;
				y_sum64_after = image_sum_grayscale64_vertical(image_buffer, image_dimensions_lcd, y_start, y_end, next_x + x_direction, lcd_convention);
			}
		}
		x_offset = -1;
	}
}

void image_hed_copy_lines(
	ImageConstBuffer image_buffer, Vector2Int image_dimensions_lcd,
	const uint16_t* line_indices, uint16_t line_count,
	Axis axis, int8_t line_direction, Color16* out_buffer)
{
	const uint16_t line_length = vector2int_get(image_dimensions_lcd, axis);
	for (uint16_t pixel_k = 0; pixel_k < line_length; pixel_k++)
	{
		const uint16_t pixel_i = (line_direction < 0)
			? (line_length - 1 - pixel_k)
			: pixel_k;
		for (uint16_t line_i = 0; line_i < line_count; line_i++)
		{
			const uint16_t line_index = line_indices[line_i];
			Vector2Int source_location; {
				source_location = vector2int_new(pixel_i, line_index);
				if (axis != 0)
					source_location = vector2int_swap(source_location);
			}
			const Color16 pixel_data = image_get_pixel(image_buffer, image_dimensions_lcd, source_location);

			const uint16_t out_index = line_length * line_i + pixel_k;
			out_buffer[out_index] = pixel_data;
		}
	}
}

uint16_t image_hed_next_search_center(const uint16_t* gradient_bounds, const uint16_t* value_bounds, uint16_t range_length)
{
	// Both gradients => middle
	if (gradient_bounds[0] != UINT16_MAX && gradient_bounds[1] != UINT16_MAX)
		return (gradient_bounds[0] + gradient_bounds[1]) / 2;

	// Both values => middle
	if (value_bounds[0] != UINT16_MAX && value_bounds[1] != UINT16_MAX)
		return (value_bounds[0] + value_bounds[1]) / 2;

	// One gradient => middle of found and edge of image
	if (gradient_bounds[0] != UINT16_MAX && gradient_bounds[1] == UINT16_MAX)
		return gradient_bounds[0] / 2;

	if (gradient_bounds[0] == UINT16_MAX && gradient_bounds[1] != UINT16_MAX)
		return (gradient_bounds[1] + range_length) / 2;

	// One value => middle of found and edge of image
	if (value_bounds[0] != UINT16_MAX && value_bounds[1] == UINT16_MAX)
		return value_bounds[0] / 2;

	if (value_bounds[0] == UINT16_MAX && value_bounds[1] != UINT16_MAX)
		return (value_bounds[1] + range_length) / 2;

	// None found => middle
	return range_length / 2;
}
