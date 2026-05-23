#ifndef CAMERA_UTILITY_H
#define CAMERA_UTILITY_H

#include "vector2int.h"

// Camera width in pixels in landscape layout for lcd
#define CAMERA_WIDTH 320
// Camera height in pixels in landscape layout for lcd
#define CAMERA_HEIGHT 240
// Camera dimensions in landscape layout for lcd
#define CAMERA_DIMENSIONS_HORIZONTAL ((Vector2Int){ .x = CAMERA_WIDTH, .y = CAMERA_HEIGHT })
// Camera dimensions in portrait layout for lcd
#define CAMERA_DIMENSIONS_VERTICAL ((Vector2Int){ .x = CAMERA_HEIGHT, .y = CAMERA_WIDTH })
// Camera pixel count
#define CAMERA_PIXEL_COUNT (CAMERA_WIDTH * CAMERA_HEIGHT)

#endif // CAMERA_UTILITY_H
