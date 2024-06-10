#include "cyclic_iterator.hpp"

CyclicIterator& CyclicIterator::operator++() {
    value = (value + 1) % max;
    return *this;
}

CyclicIterator& CyclicIterator::operator--() {
    value = (value - 1 + max) % max;
    return *this;
}

int CyclicIterator::operator*() const {
    return value;
}
