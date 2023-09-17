#include "word2vec.h"

#include <limits>
#include <vector>

int ScalarMultiplication(const std::vector<int>& v1, const std::vector<int>& v2) {
    int res{};
    for (int i = 0; i < v1.size(); ++i) {
        res += v1[i] * v2[i];
    }
    return res;
}

std::vector<std::string> FindClosestWords(const std::vector<std::string>& words,
                                          const std::vector<std::vector<int>>& vectors) {
    int max{std::numeric_limits<int>::min()};
    std::vector<std::string> res;
    for (int i = 1; i < vectors.size(); ++i) {
        auto scalar = ScalarMultiplication(vectors[0], vectors[i]);
        if (scalar > max) {
            res.clear();
            max = scalar;
        }
        if (scalar == max) {
            res.push_back(words[i]);
        }
    }
    return res;
}