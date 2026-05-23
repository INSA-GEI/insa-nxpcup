#ifndef INDEX_RANGE_H
#define INDEX_RANGE_H

#include <stdint.h>

/*!
 * @brief Range of indices with start and exclusive end
 */
typedef struct
{
    uint16_t start;
    uint16_t end;
} IndexRange;

// `IndexRange`: create with `start` and `end`
IndexRange index_range_new(uint16_t start, uint16_t end);

// `IndexRange`: create with `start` and `length`
IndexRange index_range_with_length(uint16_t start, uint16_t length);

// `IndexRange`: get length
uint16_t index_range_get_length(IndexRange range);

/// @brief Make subrange out of `original` splitting according to `indicator`
/// @param indicator In [-1; 1], multiplies the length by `indicator`,
/// if >= 0, the start is kept fixed,
/// if < 0, the end is kept fixed
/// @return The new subrange
IndexRange index_range_subrange(IndexRange original, float indicator);

#endif // INDEX_RANGE_H
