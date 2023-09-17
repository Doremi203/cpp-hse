#pragma once

#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using std::string;

template <class T>
std::vector<std::unique_ptr<T>> Duplicate(const std::vector<std::shared_ptr<T>>& items) {
    std::vector<std::unique_ptr<T>> res;
    for (auto& item : items) {
        res.emplace_back(std::make_unique<T>(*item));
    }
    return res;
}

template <class T>
std::vector<std::shared_ptr<T>> DeDuplicate(const std::vector<std::unique_ptr<T>>& items) {
    std::unordered_map<T, std::shared_ptr<T>> map;
    std::vector<std::shared_ptr<T>> res;
    for (auto& item : items) {
        if (!map.contains(*item)) {
            map[*item] = std::make_shared<T>(*item);
        }
        res.push_back(map[*item]);
    }
    return res;
}
