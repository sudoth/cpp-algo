#ifndef REVERSED_H
#define REVERSED_H
#include <utility>
#include <iterator>

template <typename Container>
class Reversed {
    private:
    Container& container_;
    
    public:
    explicit Reversed(Container& container) : container_(container) {}
    
    auto begin() {
        return container_.rbegin();
    }
    
    auto end() {
        return container_.rend();
    }
};

template <typename Container>
class Reversed<Container&&> {
    private:
    Container container_;
    
    public:
    explicit Reversed(Container&& container) : container_(std::move(container)) {}
    
    auto begin() {
        return container_.rbegin();
    }
    
    auto end() {
        return container_.rend();
    }
};

template <typename Container>
auto reversed(Container&& container) {
    return Reversed<Container&&>(std::forward<Container>(container));
}

#define TEMPORARY_REVERSED_IMPLEMENTED
#endif