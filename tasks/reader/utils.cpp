#include "utils.h"

std::unique_ptr<Reader> MakeStringReader(const std::string& data) {
    return std::unique_ptr<StringReader>(new StringReader(data));
}

TeeReader MakeTee(const std::vector<std::string>& chunks) {
    std::vector<std::unique_ptr<Reader>> readers;
    for (const auto& c : chunks) {
        readers.emplace_back(MakeStringReader(c));
    }
    return TeeReader(std::move(readers));
}