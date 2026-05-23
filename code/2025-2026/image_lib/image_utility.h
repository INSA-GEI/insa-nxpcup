#ifndef IMAGE_MUTATION_H
#define IMAGE_MUTATION_H

#include <stdint.h>
#include "color_utility.h"
#include "vector2int.h"

// Keywords before an array declaration of `Color16` meant to be a buffer (see `CAMERA_BUFFER_DECLARE` syntax)
#define CAMERA_BUFFER_ARRAY_PREFIX volatile Color16
// Array declaration of `Color16` meant to be a buffer
#define CAMERA_BUFFER_DECLARE(Name, Pixel_Count) volatile Color16 Name[Pixel_Count]

// Pointer to an image buffer
typedef volatile Color16* ImageBuffer;
// Pointer to an immutable image buffer
typedef volatile const Color16* ImageConstBuffer;

// Gets the index of `location` in an `ImageBuffer` with `dimensions`
size_t image_coordinate_to_index(Vector2Int location, Vector2Int dimensions);

// Sets the pixel in `camera_buffer` with `dimensions` at `location` to `value`
void image_set_pixel(ImageBuffer camera_buffer, Vector2Int dimensions, Vector2Int location, Color16 value);

// Gets the pixel in `camera_buffer` with `dimensions` at `location`
Color16 image_get_pixel(ImageConstBuffer camera_buffer, Vector2Int dimensions, Vector2Int location);

// Fills a rectangle with `rectangle_dimensions` in `camera_buffer` with `dimensions` at `location` to `value`
void image_fill_rectangle(
    ImageBuffer camera_buffer,
    Vector2Int camera_dimensions,
    Vector2Int location,
    Vector2Int rectangle_dimensions,
    Color16 value);

// Sets every pixel in `camera_buffer` with `dimensions` to 0 (black)
void image_clear(ImageBuffer camera_buffer, Vector2Int dimensions);

#endif // IMAGE_MUTATION_H
