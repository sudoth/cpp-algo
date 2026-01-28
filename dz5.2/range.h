#ifndef RANGE_H
#define RANGE_
#include <iterator>

class RangeIterator {
    public:
    using iterator_category = std::input_iterator_tag;
    using value_type = int;
    using difference_type = int;
    using pointer = int*;
    using reference = int&;
    
    private:
    int current_;
    int step_;
    int end_;
    bool at_end_;
    
    public:
    RangeIterator(int current, int step, int end, bool at_end = false)
    : current_(current), step_(step), end_(end), at_end_(at_end) {
        if (!at_end_ && step_ != 0) {
            if ((step_ > 0 && current_ >= end_) || (step_ < 0 && current_ <= end_)) {
                at_end_ = true;
            }
        }
    }
    
    int operator*() const {
        return current_;
    }
    
    RangeIterator& operator++() {
        current_ += step_;
        if ((step_ > 0 && current_ >= end_) || (step_ < 0 && current_ <= end_)) {
            at_end_ = true;
        }
        return *this;
    }
    
    RangeIterator operator++(int) {
        RangeIterator tmp = *this;
        ++(*this);
        return tmp;
    }
    
    bool operator!=(const RangeIterator& other) const {
        if (at_end_ != other.at_end_) {
            return !at_end_;
        }
        return current_ != other.current_;
    }
    
    bool operator==(const RangeIterator& other) const {
        return !(*this != other);
    }
};

class Range {
    private:
    int begin_;
    int end_;
    int step_;
    
    public:
    Range(int end) : begin_(0), end_(end), step_(1) {
        if (end_ <= begin_) {
            step_ = 0;
        }
    }
    
    Range(int begin, int end) : begin_(begin), end_(end), step_(1) {
        if (end_ <= begin_) {
            step_ = 0;
        }
    }
    
    Range(int begin, int end, int step) : begin_(begin), end_(end), step_(step) {
        if (step_ == 0) {
        } else if ((step_ > 0 && begin_ >= end_) || (step_ < 0 && begin_ <= end_)) {
            step_ = 0;
        }
    }
    
    RangeIterator begin() const {
        if (step_ == 0) {
            return RangeIterator(begin_, 0, end_, true);
        }
        return RangeIterator(begin_, step_, end_);
    }
    
    RangeIterator end() const {
        if (step_ == 0) {
            return RangeIterator(begin_, 0, end_, true);
        }
        return RangeIterator(end_, step_, end_, true);
    }
};

Range range(int end) {
    return Range(end);
}

Range range(int begin, int end) {
    return Range(begin, end);
}

Range range(int begin, int end, int step) {
    return Range(begin, end, step);
}

#endif