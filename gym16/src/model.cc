#include <model.hpp>

std::shared_ptr<std::array<std::array<float, 1000>, 1000>> Model::GetMatrix() {
  if (!matrix_) {
    matrix_ = std::make_shared<std::array<std::array<float, 1000>, 1000>>();
  }
  return matrix_;
}