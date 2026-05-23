#ifndef LCD_UTILITY_H
#define LCD_UTILITY_H

#include <stdint.h>

#include "st7796_lcd.h"
#include "color_utility.h"
#include "vector2int.h"
#include "image_utility.h"
#include "index_range.h"

// Height of the lcd screen in landscape layout
#define LCD_HEIGHT 320
// Width of the lcd screen in landscape layout
#define LCD_WIDTH 480
// Dimensions of the lcd screen in landscape layout
#define LCD_DIMENSIONS_LANDSCAPE ((Vector2Int){ .x = LCD_WIDTH, .y = LCD_HEIGHT })
// Vertical index range of the lcd screen in landscape layout
#define LCD_VERTICAL_INDEX_RANGE ((IndexRange){ .start = 0, .end = LCD_HEIGHT })
// Horizontal index range of the lcd screen in landscape layout
#define LCD_HORIZONTAL_INDEX_RANGE ((IndexRange){ .start = 0, .end = LCD_WIDTH })

/// @brief Load rectangle shaped pixel buffer `source` to `target` with coordinate ranges (end exclusive)
/// `x_start..x_end` and `y_start..y_end`
/// @return The return value of the underlying call to `st7796_lcd_load`
st7796_ret_t lcd_utility_load(
    st7796_lcd_t* target,
    ImageBuffer source,
    Vector2Int dimensions,
    uint16_t x_start,
    uint16_t x_end,
    uint16_t y_start,
    uint16_t y_end);

/// @brief Load rectangle shaped pixel buffer `source` to `target` from location `start_corner` to location `end_corner` exclusive
/// @return The return value of the underlying call to `st7796_lcd_load`
st7796_ret_t lcd_utility_load_corners(st7796_lcd_t* target, ImageBuffer source, Vector2Int dimensions, Vector2Int start_corner, Vector2Int end_corner);

/// @brief Load rectangle shaped pixel buffer `source` to `target` with coordinate ranges (end exclusive) `x_range` and `y_range`
/// @return The return value of the underlying call to `st7796_lcd_load`
st7796_ret_t lcd_utility_load_ranges(st7796_lcd_t* target, ImageBuffer source, Vector2Int dimensions, IndexRange x_range, IndexRange y_range);

#endif // LCD_UTILITY_H
