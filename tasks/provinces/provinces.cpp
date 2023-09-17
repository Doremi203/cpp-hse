#include "provinces.h"

#include <queue>

int64_t CountPassports(const std::vector<int>& provinces) {
    int64_t res{};
    std::priority_queue<int64_t, std::vector<int64_t>, std::greater<int64_t>> queue;
    for (auto& item : provinces) {
        queue.push(item);
    }
    while (queue.size() > 1) {
        int64_t temp{};
        temp += queue.top();
        queue.pop();
        temp += queue.top();
        queue.pop();
        queue.push(temp);
        res += temp;
    }
    return res;
}
