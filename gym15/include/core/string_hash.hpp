#pragma once

#include <string_view>

struct StringHash {
  using is_transparent = void;
  size_t operator()(std::string_view sv) const { return std::hash<std::string_view>{}(sv); }
};