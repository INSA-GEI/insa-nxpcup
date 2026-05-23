#include "vector2int.h"

#include <assert.h>

Vector2Int vector2int_new(uint16_t x, uint16_t y)
{
    return (Vector2Int){ .x = x, .y = y };
}

Vector2Int vector2int_add(Vector2Int a, Vector2Int b)
{
    return (Vector2Int){
        .x = a.x + b.x,
        .y = a.y + b.y,
    };
}

Vector2Int vector2int_sub(Vector2Int a, Vector2Int b)
{
    return (Vector2Int){
        .x = a.x - b.x,
        .y = a.y - b.y,
    };
}

Vector2Int vector2int_scale(Vector2Int v, uint16_t n)
{
    return (Vector2Int){
        .x = v.x * n,
        .y = v.y * n,
    };
}

Vector2Int vector2int_integer_divide(Vector2Int v, uint16_t n)
{
    return (Vector2Int){
        .x = v.x / n,
        .y = v.y / n,
    };
}

uint32_t vector2int_area(Vector2Int v)
{
    return v.x * v.y;
}

bool vector2int_less_than(Vector2Int a, Vector2Int b)
{
    return a.x < b.x && a.y < b.y;
}

bool vector2int_less_equal(Vector2Int a, Vector2Int b)
{
    return a.x <= b.x && a.y <= b.y;
}

uint16_t vector2int_get(Vector2Int v, Axis axis)
{
    switch (axis)
    {
        case AXIS_X: return v.x;
        case AXIS_Y: return v.y;
        default: assert(false);
    }

    return 0;
}

Vector2Int vector2int_swap(Vector2Int v)
{
    uint16_t saved_value = v.x;
    v.x = v.y;
    v.y = saved_value;
    return v;
}
