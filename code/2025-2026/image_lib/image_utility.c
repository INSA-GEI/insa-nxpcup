#include <stddef.h>
#include <assert.h>
#include <string.h>
#include "vector2int.h"

#include "image_utility.h"

size_t image_coordinate_to_index(Vector2Int location, Vector2Int dimensions)
{
    return location.x * dimensions.y + location.y;
}

void image_set_pixel(ImageBuffer camera_buffer, Vector2Int dimensions, Vector2Int location, Color16 value)
{
    assert(camera_buffer != NULL);
    assert(vector2int_less_than(location, dimensions));

    size_t index = image_coordinate_to_index(location, dimensions);
    assert(index < vector2int_area(dimensions));
    camera_buffer[index] = value;
}

Color16 image_get_pixel(ImageConstBuffer camera_buffer, Vector2Int dimensions, Vector2Int location)
{
    assert(camera_buffer != NULL);
    assert(vector2int_less_than(location, dimensions));

    size_t index = image_coordinate_to_index(location, dimensions);
    assert(index < vector2int_area(dimensions));
    return camera_buffer[index];
}

void image_fill_rectangle(
    ImageBuffer camera_buffer,
    Vector2Int camera_dimensions,
    Vector2Int location,
    Vector2Int rectangle_dimensions,
    Color16 value)
{
    assert(camera_buffer != NULL);
    assert(vector2int_less_than(location, camera_dimensions)); // Target location out of camera dimensions

    const Vector2Int maximum_location = vector2int_add(location, rectangle_dimensions);

    assert(vector2int_less_equal(maximum_location, camera_dimensions)); // Maximum location out of camera dimensions

    for (Vector2Int current = location; current.y < maximum_location.y; current.y++)
    {
        for (current.x = location.x; current.x < maximum_location.x; current.x++)
        {
            image_set_pixel(camera_buffer, camera_dimensions, current, value);
        }
    }
}

void image_clear(ImageBuffer camera_buffer, Vector2Int dimensions)
{
    assert(camera_buffer != NULL);

    size_t pixel_count = vector2int_area(dimensions);
    memset((void*)camera_buffer, 0, pixel_count * sizeof(camera_buffer[0]));
}
