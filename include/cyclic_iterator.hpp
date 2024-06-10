#pragma once

/**
 * A class that represents a cyclic iterator.
 * 
 * This class allows iterating over a range of values in a cyclic manner.
 * The iterator wraps around to the beginning when it reaches the end of the range.
 */
class CyclicIterator {
private:
    int value; /**< The current value of the iterator. */
    int max; /**< The maximum value of the iterator range. */

public:
    /**
     * Constructs a CyclicIterator object.
     * 
     * @param start The starting value of the iterator.
     * @param max The maximum value of the iterator range.
     */
    CyclicIterator(int start, int max) : value(start), max(max) {}

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
    int operator*() const;
};
