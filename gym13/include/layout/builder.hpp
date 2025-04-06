#pragma once

#include <layout/standard_layout.hpp>
#include <nlohmann/json.hpp>

inline std::shared_ptr<Layout> BuildLayoutFromJson(std::shared_ptr<Layout> default_layout,
                                                   const std::string &type) {
  if (type == "standard") {
    return std::make_shared<StandardLayout>();
  }
  return default_layout;
}
