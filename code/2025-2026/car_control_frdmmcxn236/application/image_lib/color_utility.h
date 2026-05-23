#ifndef COLOR_UTILITY_H
#define COLOR_UTILITY_H

#include <stdint.h>
#include <stdbool.h>

/*!
 * @brief 16-bit RGB565 color type
 */
typedef struct
{
    uint16_t value;
} ColorRGB;

/*!
 * @brief 16-bit YUV 4:2:2 color type
 */
typedef struct
{
    uint16_t value;
} ColorYUV;

/*!
 * @brief 16-bit color type: union of RGB565 and YUV422
 */
typedef union
{
    // Value as RGB565
    ColorRGB as_rgb;
    // Value as YUV422
    ColorYUV as_yuv;
    // Value as raw unsigned 16-bit integer
    uint16_t as_raw;
} Color16;

// Max value for color RGB565 red channel
#define COLOR_RGB_CHANNEL_MAX_RED ((1 << 5) - 1)
// Max value for color RGB565 green channel
#define COLOR_RGB_CHANNEL_MAX_GREEN ((1 << 6) - 1)
// Max value for color RGB565 blue channel
#define COLOR_RGB_CHANNEL_MAX_BLUE ((1 << 5) - 1)

#define COLOR_RGB_CHANNEL_MASK_RED   ((uint16_t)(0b1111100000000000))
#define COLOR_RGB_CHANNEL_MASK_GREEN ((uint16_t)(0b0000011111100000))
#define COLOR_RGB_CHANNEL_MASK_BLUE  ((uint16_t)(0b0000000000011111))

#define COLOR_RGB_CHANNEL_MASK5 (0b11111)
#define COLOR_RGB_CHANNEL_MASK6 (0b111111)

#define COLOR_RGB_BLACK (color16_rgb_from_int(0, 0, 0))
#define COLOR_RGB_WHITE (color16_rgb_from_int(COLOR_RGB_CHANNEL_MAX_RED, COLOR_RGB_CHANNEL_MAX_GREEN, COLOR_RGB_CHANNEL_MAX_BLUE))
#define COLOR_RGB_GREY (color16_rgb_from_int(COLOR_RGB_CHANNEL_MAX_RED / 2, COLOR_RGB_CHANNEL_MAX_GREEN / 2, COLOR_RGB_CHANNEL_MAX_BLUE / 2))
#define COLOR_RGB_RED (color16_rgb_from_int(COLOR_RGB_CHANNEL_MAX_RED, 0, 0))
#define COLOR_RGB_GREEN (color16_rgb_from_int(0, COLOR_RGB_CHANNEL_MAX_GREEN, 0))
#define COLOR_RGB_BLUE (color16_rgb_from_int(0, 0, COLOR_RGB_CHANNEL_MAX_BLUE))
#define COLOR_RGB_MAGENTA (color16_rgb_from_int(COLOR_RGB_CHANNEL_MAX_RED, 0, COLOR_RGB_CHANNEL_MAX_BLUE))
#define COLOR_RGB_ORANGE (color16_rgb_from_int(COLOR_RGB_CHANNEL_MAX_RED, COLOR_RGB_CHANNEL_MAX_GREEN / 2, 0))
#define COLOR_RGB_CYAN (color16_rgb_from_int(0, COLOR_RGB_CHANNEL_MAX_GREEN, COLOR_RGB_CHANNEL_MAX_BLUE))
#define COLOR_RGB_YELLOW (color16_rgb_from_int(COLOR_RGB_CHANNEL_MAX_RED, COLOR_RGB_CHANNEL_MAX_GREEN, 0))

// New `ColorRGB` from `value`
ColorRGB color_rgb(uint16_t value);

uint16_t color_rgb_grayscale64(ColorRGB color);

uint8_t color_rgb_r(ColorRGB color);
uint8_t color_rgb_g(ColorRGB color);
uint8_t color_rgb_b(ColorRGB color);

// New `ColorYUV` from `value`
ColorYUV color_yuv(uint16_t value);

// New `Color16` RGB variant from `value`
Color16 color16_rgb(uint16_t value);

// New `Color16` YUV variant from `value`
Color16 color16_yuv(uint16_t value);

// `Color16`: equality comparison
bool color16_equal(Color16 c1, Color16 c2);

// New `Color16` RGB variant from int values for each channel
Color16 color16_rgb_from_int(uint8_t r, uint8_t g, uint8_t b);

// New `Color16` RGB variant from float values (0 to 1) for each channel
Color16 color16_rgb_from_float(float r, float g, float b);

#endif // COLOR_UTILITY_H
