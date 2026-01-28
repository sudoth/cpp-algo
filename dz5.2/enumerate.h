#ifndef ENUMERATE_H
#define ENUMERATE_H
#include <utility>
#include <iterator>

template <typename Container>
class EnumerateIterator {
public:
    using iterator_category = std::input_iterator_tag;
    using value_type = std::pair<size_t, typename Container::value_type>;
    using difference_type = ptrdiff_t;
    using pointer = value_type*;
    using reference = value_type&;

private:
    size_t index_;
    typename Container::iterator iter_;

public:
    EnumerateIterator(size_t index, typename Container::iterator iter)
        : index_(index), iter_(iter) {}

    std::pair<size_t, typename Container::reference> operator*() {
        return {index_, *iter_};
    }

    EnumerateIterator& operator++() {
        ++index_;
        ++iter_;
        return *this;
    }

    EnumerateIterator operator++(int) {
        EnumerateIterator tmp = *this;
        ++(*this);
        return tmp;
    }

    bool operator!=(const EnumerateIterator& other) const {
        return iter_ != other.iter_;
    }

    bool operator==(const EnumerateIterator& other) const {
        return iter_ == other.iter_;
    }
};

template <typename Container>
class Enumerate {
private:
    Container& container_;

public:
    Enumerate(Container& container) : container_(container) {}

    EnumerateIterator<Container> begin() {
        return EnumerateIterator<Container>(0, container_.begin());
    }

    EnumerateIterator<Container> end() {
        return EnumerateIterator<Container>(0, container_.end());
    }
};

template <typename Container>
class Enumerate<Container&&> {
private:
    Container container_;

public:
    Enumerate(Container&& container) : container_(std::move(container)) {}

    EnumerateIterator<Container> begin() {
        return EnumerateIterator<Container>(0, container_.begin());
    }

    EnumerateIterator<Container> end() {
        return EnumerateIterator<Container>(0, container_.end());
    }
};

template <typename Container>
auto enumerate(Container&& container) {
    return Enumerate<Container&&>(std::forward<Container>(container));
}

#define TEMPORARY_ENUMERATE_IMPLEMENTED
#endif
