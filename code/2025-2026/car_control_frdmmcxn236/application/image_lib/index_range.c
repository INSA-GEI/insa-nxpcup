#include "index_range.h"

#include <assert.h>
#include <stdint.h>

IndexRange index_range_new(uint16_t start, uint16_t end)
{
    assert(start <= end); // Range is backwards
    return (IndexRange){ .start = start, .end = end };
}

IndexRange index_range_with_length(uint16_t start, uint16_t length)
{
    assert((uint32_t)start + (uint32_t)length < UINT16_MAX); // Range end overflows
    return (IndexRange){ .start = start, .end = start + length };
}

uint16_t index_range_get_length(IndexRange range)
{
    assert(range.start <= range.end); // Range is backwards
    return range.end - range.start;
}

IndexRange index_range_subrange(IndexRange original, float indicator)
{
    assert(-1.0F <= indicator && indicator <= 1.0F);

    // Add 0.5 then cast to integer (floor) <=> round
    const float ROUND_TO_NEAREST = 0.5F;
    const uint16_t length = index_range_get_length(original);

    if (indicator < 0)
    {
        return index_range_new(
            (uint16_t)(original.end + length * indicator + ROUND_TO_NEAREST),
            original.end
        );
    }

    return index_range_new(
        original.start,
        (uint16_t)(original.start + length * indicator + ROUND_TO_NEAREST)
    );
}
