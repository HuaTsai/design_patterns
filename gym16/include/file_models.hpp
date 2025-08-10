#pragma once

#include <filesystem>
#include <models.hpp>

class FileModels : public Models {
 public:
  using Models::Models;
  std::shared_ptr<Model> CreateModel(const std::string &name) override;
};
