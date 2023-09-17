#include "readers_util.h"

LimitReader::LimitReader(std::unique_ptr<Reader> reader, size_t limit) : reader_(std::move(reader)), limit_(limit) {
}

size_t LimitReader::Read(char *buf, size_t len) {
    auto res = reader_->Read(buf, std::min(len, limit_));
    limit_ = 0;
    return res;
}

TeeReader::TeeReader(std::vector<std::unique_ptr<Reader>> readers) : readers_(std::move(readers)) {
}

size_t TeeReader::Read(char *buf, size_t len) {
    current_ = 0;
    for (auto &reader : readers_) {
        current_ += reader->Read(&buf[current_], len);
    }
    return current_;
}

HexDecodingReader::HexDecodingReader(std::unique_ptr<Reader> reader) : reader_(std::move(reader)) {
}

size_t HexDecodingReader::Read(char *buf, size_t len) {
    const int hex_length = 16;
    auto temp = new char[len];
    auto res = reader_->Read(temp, len);
    auto chr_count{0};
    for (int i = 0; i < res; i += 2) {
        auto byte = std::string(&temp[i], 2);
        char chr = static_cast<char>(std::stoul(byte, nullptr, hex_length));
        buf[chr_count++] = chr;
    }
    delete[] temp;
    return chr_count;
}
