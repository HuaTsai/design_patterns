#pragma once

#include <model.hpp>
#include <mutex>

class MultiplicationModel : public Model {
 public:
  explicit MultiplicationModel(const std::filesystem::path &model_path);
  std::array<float, 1000> LinearTransformation(const std::array<float, 1000> &vector) override;

 private:
  void LoadModelFromFilePath();

  inline static std::filesystem::path current_model_path_{""};
  inline static std::mutex mutex_;
  std::filesystem::path model_path_;
};
