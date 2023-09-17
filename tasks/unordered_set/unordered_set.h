#pragma once

#include <list>
#include <vector>

template <typename KeyT>
class UnorderedSet {
public:
    UnorderedSet() : n_elements_(), data_() {
    }

    explicit UnorderedSet(size_t count) : n_elements_(), data_(count, std::list<KeyT>()) {
    }

    template <typename IteratorType,
              typename = std::enable_if_t<std::is_base_of_v<
                  std::forward_iterator_tag, typename std::iterator_traits<IteratorType>::iterator_category>>>
    UnorderedSet(IteratorType first, IteratorType last) : n_elements_() {
        for (auto i = first; i != last; ++i) {
            Insert(*i);
        }
    }

    UnorderedSet(const UnorderedSet& other) : n_elements_(other.n_elements_), data_(other.data_) {
    }

    UnorderedSet(UnorderedSet&& other) : n_elements_(other.n_elements_), data_(std::move(other.data_)) {
        other.n_elements_ = 0;
    }

    ~UnorderedSet() = default;

    UnorderedSet& operator=(const UnorderedSet& other) {
        if (this != &other) {
            data_ = other.data_;
            n_elements_ = other.n_elements_;
        }
        return *this;
    }

    UnorderedSet& operator=(UnorderedSet&& other) {
        if (this != &other) {
            data_ = std::move(other.data_);
            n_elements_ = other.n_elements_;
            other.n_elements_ = 0;
        }
        return *this;
    }

    size_t Size() const {
        return n_elements_;
    }

    bool Empty() const {
        return n_elements_ == 0;
    }

    void Clear() {
        data_.clear();
        n_elements_ = 0;
    }

    void Insert(const KeyT& key) {
        if (BucketCount() == 0) {
            data_.push_back(std::list<KeyT>());
        } else if (Find(key)) {
            return;
        } else if (LoadFactor() == 1) {
            Rehash(BucketCount() * 2);
        }
        ++n_elements_;
        data_[Bucket(key)].push_back(key);
    }

    void Insert(KeyT&& key) {
        if (BucketCount() == 0) {
            data_.push_back(std::list<KeyT>());
        } else if (Find(key)) {
            return;
        } else if (LoadFactor() == 1) {
            Rehash(BucketCount() * 2);
        }
        ++n_elements_;
        data_[Bucket(key)].push_back(std::move(key));
    }

    void Erase(const KeyT& key) {
        --n_elements_;
        data_[Bucket(key)].remove(key);
    }

    bool Find(const KeyT& key) const {
        if (!BucketCount()) {
            return false;
        }
        return data_[Bucket(key)].end() != std::find(data_[Bucket(key)].begin(), data_[Bucket(key)].end(), key);
    }

    void Rehash(size_t new_bucket_count) {
        if (new_bucket_count >= Size()) {
            std::vector<std::list<KeyT>> temp(data_);
            data_ = std::vector<std::list<KeyT>>(new_bucket_count, std::list<KeyT>());
            n_elements_ = 0;
            for (auto& list : temp) {
                for (auto& item : list) {
                    Insert(item);
                }
            }
        }
    }

    void Reserve(size_t new_bucket_count) {
        if (new_bucket_count > BucketCount()) {
            auto temp = new_bucket_count - BucketCount();
            for (int i = 0; i < temp; ++i) {
                data_.push_back(std::list<KeyT>());
            }
        }
    }

    size_t BucketCount() const {
        return data_.size();
    }

    size_t BucketSize(size_t id) const {
        if (id >= BucketCount()) {
            return 0;
        }
        return data_[id].size();
    }

    size_t Bucket(const KeyT& key) const {
        if (BucketCount()) {
            return std::hash<KeyT>{}(key) % BucketCount();
        }
        return 0;
    }

    double LoadFactor() const {
        if (!BucketCount()) {
            return 0;
        }
        return static_cast<double>(n_elements_) / BucketCount();
    }

private:
    size_t n_elements_;
    std::vector<std::list<KeyT>> data_;
};
