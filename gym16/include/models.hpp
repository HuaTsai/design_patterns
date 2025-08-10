#pragma once

#include <model.hpp>

class Models {
 public:
  Models() = default;
  Models(const Models &) = delete;
  Models &operator=(const Models &) = delete;
  Models(Models &&) = delete;
  Models &operator=(Models &&) = delete;

  virtual ~Models() = default;

  virtual std::shared_ptr<Model> CreateModel(const std::string &name) = 0;
};
