#ifndef VECTOR2INT_H
#define VECTOR2INT_H

#include <stdint.h>
#include <stdbool.h>

/*!
 * @brief 2 dimensional vector of uint16
 */
typedef struct
{
    uint16_t x;
    uint16_t y;
} Vector2Int;

typedef enum
{
    AXIS_X = 0,
    AXIS_Y = 1
} Axis;

/*!
 * @brief New `Vector2Int` value
 */
Vector2Int vector2int_new(uint16_t x, uint16_t y);

/*!
 * @brief Vector addition: a + b
 */
Vector2Int vector2int_add(Vector2Int a, Vector2Int b);

/*!
 * @brief Vector subtraction: a - b
 */
Vector2Int vector2int_sub(Vector2Int a, Vector2Int b);

/*!
 * @brief Vector to scalar multiplication
 */
Vector2Int vector2int_scale(Vector2Int v, uint16_t n);

/*!
 * @brief Vector to scalar integer division (v.x / n, v.y / n)
 */
Vector2Int vector2int_integer_divide(Vector2Int v, uint16_t n);

/*!
 * @brief Vector component product (v.x * v.y)
 */
uint32_t vector2int_area(Vector2Int v);

/*!
 * @brief Component-wise less-than compatison (a.x < b.x && a.y < b.y)
 */
bool vector2int_less_than(Vector2Int a, Vector2Int b);

/*!
 * @brief Component-wise less-than compatison (a.x <= b.x && a.y <= b.y)
 */
bool vector2int_less_equal(Vector2Int a, Vector2Int b);

/*!
 * @brief Get value from `v` for `axis`
 */
uint16_t vector2int_get(Vector2Int v, Axis axis);

/*!
 * @brief Get `v` with axes swapped
 */
Vector2Int vector2int_swap(Vector2Int v);

#endif // VECTOR2INT_H
