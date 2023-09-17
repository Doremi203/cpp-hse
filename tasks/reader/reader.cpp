#include "reader.h"

std::string ReadAll(Reader* in) {
    const size_t chunk_size = 128;

    std::string buf;
    std::string chunk;
    while (true) {
        chunk.resize(chunk_size);
        size_t read_res = in->Read(&(chunk[0]), chunk.size());
        if (read_res == 0) {
            break;
        }
        chunk.resize(read_res);
        buf += chunk;
    }

    return buf;
}

StringReader::StringReader(const std::string& data) : data_(data) {
}

size_t StringReader::Read(char* buf, size_t len) {
    size_t read_len = std::min(len, data_.size() - pos_);
    for (size_t i = 0; i < read_len; ++i) {
        buf[i] = data_[pos_++];
    }
    return read_len;
}

FdReader::FdReader(int fd) : fd_(fd) {
}

size_t FdReader::Read(char* buf, size_t len) {
    ssize_t res = ::read(fd_, buf, len);
    if (res == -1) {  // treat errors as EOF
        res = 0;
    }
    return res;
}
