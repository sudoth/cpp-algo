#ifndef UNORDERED_SET_H
#define UNORDERED_SET_H
#include <algorithm>
#include <vector>
#include <list>
#include <forward_list>
#include <iostream>
#include <string>

template <class KeyT>
class UnorderedSet {
  public:
  UnorderedSet() : pre_factor_(0), size_(0) {
  }
  
  explicit UnorderedSet(size_t count) : un_set_(std::vector<std::list<KeyT>>(count)), pre_factor_(0), size_(0) {
  }
  
  UnorderedSet(const typename std::forward_list<KeyT>::iterator begin,
    const typename std::forward_list<KeyT>::iterator finish) {
      size_t size = 0;
      typename std::forward_list<KeyT>::iterator c_b = begin;
      while (c_b != finish) {
        size++;
        c_b++;
      }
      un_set_ = std::vector<std::list<KeyT>>(size);
      c_b = begin;
      while (c_b != finish) {
        un_set_[std::hash<KeyT>{}(*c_b) % un_set_.size()].push_front(*c_b);
        c_b++;
      }
      size_ = size;
      pre_factor_ = 1;
    }
    
    UnorderedSet(const UnorderedSet &other) {
      for (auto &part : other.un_set_) {
        un_set_.push_back(part);
      }
      size_ = other.size_;
      pre_factor_ = other.pre_factor_;
    }
    
    UnorderedSet(UnorderedSet &&other) {
      for (auto &part : other.un_set_) {
        un_set_.push_back(std::move(part));
      }
      size_ = other.size_;
      pre_factor_ = other.pre_factor_;
      other.un_set_.clear();
      other.pre_factor_ = 0;
      other.size_ = 0;
    }
    
    UnorderedSet &operator=(const UnorderedSet &other) {
      un_set_.clear();
      size_ = other.size_;
      pre_factor_ = other.pre_factor_;
      for (auto &element : other.un_set_) {
        un_set_.push_back(element);
      }
      return (*this);
    }
    
    UnorderedSet &operator=(UnorderedSet &&other) {
      if (this != &other) {
        un_set_.clear();
        size_ = other.size_;
        pre_factor_ = other.pre_factor_;
        for (auto &element : other.un_set_) {
          un_set_.push_back(std::move(element));
        }
        other.un_set_.clear();
        other.pre_factor_ = 0;
        other.size_ = 0;
      }
      return *this;
    }
    
    size_t Size() const {
      return size_;
    }
    
    bool Empty() const {
      return size_ == 0;
    }
    
    void Insert(const KeyT &k_t) {
      if (size_ >= un_set_.size()) {
        if (size_ == 0) {
          Reserve(1);
        } else {
          Reserve(size_ * 2);
        }
      }
      un_set_[std::hash<KeyT>{}(k_t) % un_set_.size()].push_front(k_t);
      size_++;
      pre_factor_ = static_cast<double>(size_) / un_set_.size();
    }
    
    void Insert(KeyT &&k_t) {
      if (size_ >= un_set_.size()) {
        if (size_ == 0) {
          Reserve(1);
        } else {
          Reserve(size_ * 2);
        }
      }
      un_set_[std::hash<KeyT>{}(k_t) % un_set_.size()].push_back(k_t);
      size_++;
      pre_factor_ = static_cast<double>(size_) / un_set_.size();
    }
    
    void Erase(const KeyT &k_t) {
      if (size_ > 0) {
        auto hash = std::hash<KeyT>{}(k_t) % un_set_.size();
        auto index = std::find(un_set_[hash].begin(), un_set_[hash].end(), k_t);
        if (index != un_set_[hash].end()) {
          un_set_[hash].erase(index);
          size_--;
        }
      }
    }
    
    bool Find(const KeyT &k_t) const {
      bool ex = false;
      if (!un_set_.empty()) {
        size_t index = std::hash<KeyT>{}(k_t) % un_set_.size();
        if (!un_set_[index].empty()) {
          ex = std::find(un_set_[index].begin(), un_set_[index].end(), k_t) != un_set_[index].end();
        }
      }
      return ex;
    }
    
    void Rehash(size_t new_bucket_count) {
      size_t capacity = un_set_.size();
      if (!((new_bucket_count == capacity) || (new_bucket_count < size_))) {
        std::vector<std::list<KeyT>> buff(new_bucket_count);
        for (auto &i : un_set_) {
          for (auto &list : i) {
            buff[std::hash<KeyT>{}(list) % new_bucket_count].push_back(std::move(list));
          }
        }
        double tmp = (pre_factor_ * capacity) / new_bucket_count;
        pre_factor_ = tmp;
        un_set_ = std::move(buff);
      }
    }
    
    void Clear() {
      un_set_.clear();
      size_ = 0;
      pre_factor_ = 0;
    }
    
    size_t BucketCount() const {
      return un_set_.size();
    }
    
    size_t BucketSize(size_t i) const {
      if (i < un_set_.size()) {
        return un_set_[i].size();
      }
      return 0;
    }
    
    double LoadFactor() const {
      return pre_factor_;
    }
    
    size_t Bucket(KeyT key_t) const {
      return std::hash<KeyT>{}(key_t) % un_set_.size();
    }
    
    void Reserve(size_t new_bucket_count) {
      size_t capacity = un_set_.size();
      if (new_bucket_count > capacity) {
        std::vector<std::list<KeyT>> buff(new_bucket_count);
        for (auto &element : un_set_) {
          for (auto &list : element) {
            buff[std::hash<KeyT>{}(list) % new_bucket_count].push_back(std::move(list));
          }
        }
        pre_factor_ *= capacity / new_bucket_count;
        un_set_ = std::move(buff);
      }
    }
    
    private:
    std::vector<std::list<KeyT>> un_set_;
    double pre_factor_;
    size_t size_;
  };
#endif