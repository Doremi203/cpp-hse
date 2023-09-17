#pragma once

#include <unistd.h>

#include <algorithm>
#include <string>

class Reader {
public:
    virtual ~Reader() {
    }

    // Читает не более чем @len байт из потока.
    // Помещает результат чтения в буффер @buf.
    // Возвращает, сколько байт удалось прочитать.
    // Возвращаемое значение 0 означает конец потока.

    virtual size_t Read(char* buf, size_t len) = 0;
};

std::string ReadAll(Reader* in);

class StringReader : public Reader {
public:
    explicit StringReader(const std::string& data);

    size_t Read(char* buf, size_t len) override;

private:
    std::string data_;
    size_t pos_ = 0;
};

class FdReader : public Reader {
public:
    explicit FdReader(int fd);

    size_t Read(char* buf, size_t len) override;

private:
    int fd_;
};
