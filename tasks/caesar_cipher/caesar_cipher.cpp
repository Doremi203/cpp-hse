#include "caesar_cipher.h"

std::string Decipher(const std::string& cipher, size_t shift) {
    std::string res{};
    const int alphabet = 26;
    for (auto ch : cipher) {
        int temp = (ch - 'A' - static_cast<int>(shift) + alphabet) % alphabet;
        res += static_cast<char>(temp + 'A');
    }
    return res;
}
