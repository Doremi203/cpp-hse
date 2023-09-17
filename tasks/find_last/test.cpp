#include <algorithm>
#include <iterator>
#include <numeric>
#include <random>
#include <string>
#include <type_traits>
#include <unordered_map>
#include <vector>

#include "catch.hpp"
#include "find_last.h"

class RandomGenerator {
public:
    explicit RandomGenerator(uint32_t seed) : gen_(seed) {
    }

    template <class T>
    std::vector<T> GenIntegralVector(size_t count, T from, T to) {
        std::uniform_int_distribution<T> dist(from, to);
        std::vector<T> result(count);
        for (auto& cur : result) {
            cur = dist(gen_);
        }
        return result;
    }

    std::vector<double> GenRealVector(size_t count, double from, double to) {
        std::uniform_real_distribution<double> dist(from, to);
        std::vector<double> result(count);
        for (auto& cur : result) {
            cur = dist(gen_);
        }
        return result;
    }

    std::vector<int> GenPermutation(size_t count) {
        std::vector<int> result(count);
        std::iota(result.begin(), result.end(), 0);
        std::shuffle(result.begin(), result.end(), gen_);
        return result;
    }

    template <class T>
    T GenInt(T from, T to) {
        std::uniform_int_distribution<T> dist(from, to);
        return dist(gen_);
    }

    template <class T>
    T GenInt() {
        return GenInt(std::numeric_limits<T>::min(), std::numeric_limits<T>::max());
    }

    template <class Iterator>
    void Shuffle(Iterator first, Iterator last) {
        std::shuffle(first, last, gen_);
    }

private:
    std::mt19937 gen_;
};

struct Int {
    Int() {
    }
    Int(int x) : x(x) {
    }
    int x;

    bool operator==(const Int& r) const {
        return x == r.x;
    }
};

TEST_CASE("Simple") {
    std::vector<std::string> data{"aba", "caba", "aba"};
    auto it = FindLast(data.begin(), data.end(), "aba");

    REQUIRE(it == data.begin() + 2);
}

TEST_CASE("Empty") {
    std::vector<std::string> data;
    REQUIRE(data.begin() == FindLast(data.begin(), data.end(), ""));
}

TEST_CASE("Small") {
    std::vector<int> one{1};
    REQUIRE(one.begin() == FindLast(one.begin(), one.end(), 1));
    REQUIRE(one.end() == FindLast(one.begin(), one.end(), 0));
}

TEST_CASE("EqualOnly") {
    std::vector<Int> elems{Int(1), Int(2), Int(1), Int(3)};
    REQUIRE(elems.begin() + 2 == FindLast(elems.begin(), elems.end(), Int(1)));
}

const int SEED = 85475;

TEST_CASE("Long") {
    RandomGenerator rnd(SEED);
    const int count = 1e5;
    const int val = 100;
    std::vector<int> elems(count);
    std::unordered_map<int, int> last_positions;
    for (int i = 0; i < count; ++i) {
        elems[i] = rnd.GenInt(-val, val);
        last_positions[elems[i]] = i;
    }

    for (int i = -val; i <= val; ++i) {
        auto it = FindLast(elems.begin(), elems.end(), i);
        auto map_it = last_positions.find(i);
        auto distance = std::distance(elems.begin(), it);
        REQUIRE(((it == elems.end() && map_it == last_positions.end()) || distance == map_it->second));
    }
}
