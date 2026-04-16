#ifndef IMAGE_DEBUGGING_H
#define IMAGE_DEBUGGING_H

#include <stdint.h>
#include <stddef.h>

#include "image_utility.h"

// Print `length` bytes of `image` to the debug console using `PRINTF`
void print_whole_image(ImageConstBuffer image, size_t length);

#endif // IMAGE_DEBUGGING_H
