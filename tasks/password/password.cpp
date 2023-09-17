#include "password.h"

#include <cctype>

bool ValidatePassword(const std::string& password) {
    const int min_possible_ascii_value{33};
    const int max_possible_ascii_value{126};
    const int min_password_length{8};
    const int max_password_length{14};
    bool has_upper{false};
    bool has_lower{false};
    bool has_digit{false};
    bool has_other{false};
    bool is_valid_length{min_password_length <= password.length() && password.length() <= max_password_length};
    if (!is_valid_length) {
        return false;
    }
    for (auto ch : password) {
        if (ch < min_possible_ascii_value || ch > max_possible_ascii_value) {
            return false;
        }
        if (islower(ch)) {
            has_lower = true;
        } else if (isupper(ch)) {
            has_upper = true;
        } else if (isdigit(ch)) {
            has_digit = true;
        } else {
            has_other = true;
        }
    }
    return has_upper + has_lower + has_digit + has_other >= 3;
}
