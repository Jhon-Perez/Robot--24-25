#pragma once
#include <cstdint>

/**
 * A class that represents a cyclic iterator.
 * 
 * This class allows iterating over a range of values in a cyclic manner.
 * The iterator wraps around to the beginning when it reaches the end of the range.
 */
class CyclicIterator {
public:
    /**
     * Constructs a CyclicIterator object.
     * 
     * @param start The starting value of the iterator.
     * @param max The maximum value of the iterator range.
     * @param inclusive Whether the maximum value is inclusive or exclusive.
     */
    CyclicIterator(uint8_t start, uint8_t max, bool inclusive) : value(start), max(max + inclusive) {}

    /**
     * Constructs a CyclicIterator object with a default starting value of 0.
     * 
     * @param max The maximum value of the iterator range.
     * @param inclusive Whether the maximum value is inclusive or exclusive.
     */
    CyclicIterator(uint8_t max, bool inclusive) : CyclicIterator(0U, max, inclusive) {}

    /**
     * Advances the iterator to the next value.
     * 
     * @return A reference to the updated iterator.
     */
    CyclicIterator& operator++();

    /**
     * Moves the iterator to the previous value.
     * 
     * @return A reference to the updated iterator.
     */
    CyclicIterator& operator--();

    /**
     * Returns the current value of the iterator.
     * 
     * @return The current value of the iterator.
     */
    uint8_t operator*() const;

private:
    uint8_t value; /**< The current value of the iterator. */
    uint8_t max; /**< The maximum value of the iterator range. */    
};
