#include "reader.h"
#include "readers_util.h"

std::unique_ptr<Reader> MakeStringReader(const std::string& data);

TeeReader MakeTee(const std::vector<std::string>& chunks);
