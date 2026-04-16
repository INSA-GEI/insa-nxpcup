#include "color_utility.h"

#include <assert.h>
#include <stdint.h>
#include <stdbool.h>

ColorRGB color_rgb(uint16_t value)
{
    return (ColorRGB){ value };
}

uint16_t color_rgb_grayscale64(ColorRGB color)
{
    uint16_t r_64 = color_rgb_r(color) << 1;
    uint16_t g_64 = color_rgb_g(color) << 0;
    uint16_t b_64 = color_rgb_b(color) << 1;

    uint16_t adjusted_r = ((uint16_t)r_64) * 299;
    uint16_t adjusted_g = ((uint16_t)g_64) * 587;
    uint16_t adjusted_b = ((uint16_t)b_64) * 114;

    return ((uint32_t)adjusted_r + (uint32_t)adjusted_g + (uint32_t)adjusted_b) / 1000;
    // 0.299 * r + 0.587 * g + 0.114 * b
}

uint8_t color_rgb_r(ColorRGB color)
{
    return (color.value >> (0 + 6 + 5)) & COLOR_RGB_CHANNEL_MASK5;
}

uint8_t color_rgb_g(ColorRGB color)
{
    return (color.value >> (0 + 0 + 5)) & COLOR_RGB_CHANNEL_MASK6;
}

uint8_t color_rgb_b(ColorRGB color)
{
    return (color.value >> (0 + 0 + 0)) & COLOR_RGB_CHANNEL_MASK5;
}

ColorYUV color_yuv(uint16_t value)
{
    return (ColorYUV){ value };
}

Color16 color16_rgb(uint16_t value)
{
    return (Color16){ .as_yuv = color_yuv(value) };
}

Color16 color16_yuv(uint16_t value)
{
    return (Color16){ .as_rgb = color_rgb(value) };
}

bool color16_equal(Color16 c1, Color16 c2)
{
    return c1.as_raw == c2.as_raw;
}

Color16 color16_rgb_from_int(uint8_t r, uint8_t g, uint8_t b)
{
    assert(r <= COLOR_RGB_CHANNEL_MAX_RED);
    assert(g <= COLOR_RGB_CHANNEL_MAX_GREEN);
    assert(b <= COLOR_RGB_CHANNEL_MAX_BLUE);

    return color16_rgb((r << (5 + 6)) | (g << 5) | (b << 0));
}

Color16 color16_rgb_from_float(float r, float g, float b)
{
    assert(0.0F <= r && r <= 1.0F);
    assert(0.0F <= g && g <= 1.0F);
    assert(0.0F <= b && b <= 1.0F);

    return color16_rgb_from_int(
        (uint8_t)(r * COLOR_RGB_CHANNEL_MAX_RED + 0.5F),
        (uint8_t)(g * COLOR_RGB_CHANNEL_MAX_GREEN + 0.5F),
        (uint8_t)(b * COLOR_RGB_CHANNEL_MAX_BLUE + 0.5F)
    );
}
