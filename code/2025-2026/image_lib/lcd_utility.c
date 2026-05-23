#include "lcd_utility.h"

#include <assert.h>

st7796_ret_t lcd_utility_load(
    st7796_lcd_t* target,
    ImageBuffer source,
    Vector2Int dimensions,
    uint16_t x_start,
    uint16_t x_end,
    uint16_t y_start,
    uint16_t y_end)
{
    assert(x_start <= x_end); // X range is backwards
    assert(y_start <= y_end); // Y range is backwards
    assert(x_end - x_start <= dimensions.x); // X range is longer than buffer width
    assert(y_end - y_start <= dimensions.y); // Y range is longer than buffer height
    return st7796_lcd_load(target, (uint8_t*)source, y_start, y_end - 1, x_start, x_end - 1);
}

st7796_ret_t lcd_utility_load_corners(st7796_lcd_t* target, ImageBuffer source, Vector2Int dimensions, Vector2Int start_corner, Vector2Int end_corner)
{
    return lcd_utility_load(target, source, dimensions, start_corner.x, end_corner.x, start_corner.y, end_corner.y);
}

st7796_ret_t lcd_utility_load_ranges(st7796_lcd_t* target, ImageBuffer source, Vector2Int dimensions, IndexRange x_range, IndexRange y_range)
{
    return lcd_utility_load(target, source, dimensions, x_range.start, x_range.end, y_range.start, y_range.end);
}
