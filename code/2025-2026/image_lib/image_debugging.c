#include <stdint.h>
#include <stddef.h>

#include "fsl_debug_console.h"
#include "image_utility.h"
#include "image_debugging.h"

void print_whole_image(ImageConstBuffer image, size_t length)
{
    PRINTF("Image buffer: (");
    if (image == NULL)
    {
        PRINTF("(");
        return;
    }

    for (size_t i = 0; i < length; i++)
    {
        PRINTF("%x", image[i].as_raw);
        if ((i % 20) == 0)
            PRINTF("\n");
        else if (i + 1 < length)
            PRINTF(" ");
    }
}
