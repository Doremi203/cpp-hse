#include "unixpath.h"

#include <string_view>
#include <vector>

std::vector<std::string_view> Split(std::string_view string_view) {
    std::vector<std::string_view> res;
    int ptr{};
    while (!string_view.empty()) {
        if (string_view[ptr] == '/') {
            int to_remove{1};
            if (string_view[ptr + 1] == '/') {
                ++to_remove;
            }
            std::string_view temp;
            if (!(temp = string_view.substr(0, ptr)).empty()) {
                res.push_back(temp);
            }
            string_view.remove_prefix(ptr + to_remove);
            ptr = 0;
        } else if (string_view[ptr] == '\0') {
            std::string_view temp;
            if (!(temp = string_view.substr(0, ptr)).empty()) {
                res.push_back(temp);
            }
            break;
        } else {
            ++ptr;
        }
    }
    return res;
}

std::string NormalizePath(std::string_view current_working_dir, std::string_view path) {
    while (path.back() == '/' && path.size() > 1) {
        path.remove_suffix(1);
    }
    while (path.starts_with("//")) {
        path.remove_prefix(1);
    }
    if (current_working_dir.starts_with(path)) {
        return std::string{path};
    }
    std::string res{};
    std::vector<std::string_view> stack;
    auto split_str = Split(current_working_dir);
    for (const auto& item : split_str) {
        stack.push_back(item);
    }
    split_str = Split(path);
    for (const auto& item : split_str) {
        if (item.starts_with("..") && !stack.empty()) {
            stack.pop_back();
        } else if (!item.starts_with('.')) {
            stack.push_back(item);
        }
    }

    for (auto& item : stack) {
        res += '/';
        res += item;
    }
    if (res.empty()) {
        return "/";
    }
    return res;
}
