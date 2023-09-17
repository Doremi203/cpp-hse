#include "cstring.h"

#include <algorithm>
#include <unordered_map>

size_t Strlen(const char* str) {
    const char* end = str;
    while (*end != '\0') {
        ++end;
    }
    return end - str;
}

int Strcmp(const char* first, const char* second) {
    auto len1 = Strlen(first);
    auto len2 = Strlen(second);
    if (len1 == len2) {
        for (int i = 0; i < len1; ++i) {
            if (first[i] != second[i]) {
                break;
            }
            if (i == len1 - 1) {
                return 0;
            }
        }
    }
    if (std::lexicographical_compare(first, first + len1, second, second + len2)) {
        return -1;
    }
    return 1;
}

int Strncmp(const char* first, const char* second, size_t count) {
    auto len1 = Strlen(first);
    auto len2 = Strlen(second);
    if (len1 == len2) {
        if (len1 == 0) {
            return 0;
        }
        for (int i = 0; i < count; ++i) {
            if (first[i] != second[i]) {
                break;
            }
            if (i == len1 - 1 || i == count - 1) {
                return 0;
            }
        }
    }
    if (std::lexicographical_compare(first, first + count, second, second + count)) {
        return -1;
    }
    return 1;
}

char* Strcpy(char* dest, const char* src) {
    int i{};
    while (src[i] != '\0') {
        dest[i] = src[i];
        ++i;
    }
    dest[i] = '\0';
    return dest;
}

char* Strncpy(char* dest, const char* src, size_t count) {
    int i{};
    while (i < count && src[i] != '\0') {
        dest[i] = src[i];
        ++i;
    }
    if (count > Strlen(src)) {
        while (dest[i] != '\0') {
            dest[i] = '\0';
            ++i;
        }
    }
    return dest;
}

char* Strcat(char* dest, const char* src) {
    for (size_t i = Strlen(dest); *src != '\0'; ++i) {
        dest[i] = *src++;
    }
    return dest;
}

char* Strncat(char* dest, const char* src, size_t count) {
    size_t len = Strlen(dest);
    for (size_t i = Strlen(dest); (i - len) != count && *src != '\0'; ++i) {
        dest[i] = *src++;
    }
    return dest;
}

const char* Strchr(const char* str, char symbol) {
    while (*str != '\0') {
        if (*str == symbol) {
            return str;
        }
        ++str;
    }
    if (symbol == '\0') {
        return str;
    }
    return nullptr;
}

const char* Strrchr(const char* str, char symbol) {
    const char* res = nullptr;
    while (*str != '\0') {
        if (*str == symbol) {
            res = str;
        }
        ++str;
    }
    if (symbol == '\0') {
        return str;
    }
    return res;
}

size_t Strspn(const char* dest, const char* src) {
    size_t res{};
    std::unordered_map<char, int> map;
    while (*src != '\0') {
        ++map[*src++];
    }
    while (*dest != '\0') {
        if (map.contains(*dest)) {
            --map[*dest];
            ++res;
        }
        ++dest;
    }
    return res;
}

size_t Strcspn(const char* dest, const char* src) {
    size_t res{};
    std::unordered_map<char, int> map;
    while (*src != '\0') {
        ++map[*src++];
    }
    while (*dest != '\0') {
        if (map.contains(*dest++)) {
            break;
        }
        ++res;
    }
    return res;
}

const char* Strpbrk(const char* dest, const char* breakset) {
    std::unordered_map<char, int> map;
    while (*breakset != '\0') {
        ++map[*breakset++];
    }
    while (*dest != '\0') {
        if (map.contains(*dest)) {
            return dest;
        }
        ++dest;
    }
    return nullptr;
}

const char* Strstr(const char* str, const char* pattern) {
    if (*pattern == '\0') {
        return str;
    }
    auto pattern_len = Strlen(pattern);
    auto str_len = Strlen(str);
    for (int i = 0; i < str_len; ++i) {
        for (int j = i; j - i < pattern_len; ++j) {
            if (str[j] != pattern[j - i]) {
                break;
            }
            if (j - i == pattern_len - 1) {
                return &str[i];
            }
        }
    }
    return nullptr;
}