#include <fstream>
#include <multiplication_model.hpp>
#include <print>

MultiplicationModel::MultiplicationModel(const std::filesystem::path &model_path)
    : model_path_(model_path) {}

void MultiplicationModel::LoadModelFromFilePath() {
  if (model_path_ != current_model_path_) {
    std::ifstream ifs(model_path_);
    if (!ifs) {
      throw std::runtime_error("Failed to open model file: " + model_path_.string());
    }

    auto mtx = GetMatrix();
    for (size_t i = 0; i < 1000; ++i) {
      for (size_t j = 0; j < 1000; ++j) {
        ifs >> (*mtx)[i][j];  // NOLINT
      }
    }

    current_model_path_ = model_path_;
  }
}

std::array<float, 1000> MultiplicationModel::LinearTransformation(
    const std::array<float, 1000> &vector) {
  const std::lock_guard<std::mutex> lock(mutex_);
  LoadModelFromFilePath();

  auto mtx = GetMatrix();
  std::array<float, 1000> result{};

  for (size_t i = 0; i < 1000; ++i) {
    for (size_t j = 0; j < 1000; ++j) {
      result[i] += (*mtx)[i][j] * vector[j];  // NOLINT
    }
  }

  return result;
}
