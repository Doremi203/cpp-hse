#include "palindrome.h"

bool IsPalindrome(const std::string& str) {
    for (size_t forward = 0, backward = (str.length() == forward) ? 0 : str.length() - 1; forward < backward;
         ++forward, --backward) {
        while (forward < backward && str[forward] == ' ') {
            ++forward;
        }
        while (backward > forward && str[backward] == ' ') {
            --backward;
        }
        if (str[forward] != str[backward]) {
            return false;
        }
    }
    return true;
}
