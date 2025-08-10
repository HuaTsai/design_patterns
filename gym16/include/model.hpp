#pragma once

#include <array>
#include <filesystem>
#include <memory>

class Model {
 public:
  Model() = default;
  Model(const Model &) = delete;
  Model &operator=(const Model &) = delete;
  Model(Model &&) = delete;
  Model &operator=(Model &&) = delete;

  virtual ~Model() = default;

  static std::shared_ptr<std::array<std::array<float, 1000>, 1000>> GetMatrix();
  virtual std::array<float, 1000> LinearTransformation(const std::array<float, 1000> &vector) = 0;

 private:
  inline static std::shared_ptr<std::array<std::array<float, 1000>, 1000>> matrix_{nullptr};
};
