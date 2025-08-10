#include <file_models.hpp>
#include <multiplication_model.hpp>

std::shared_ptr<Model> FileModels::CreateModel(const std::string &name) {
  const std::filesystem::path base = std::filesystem::path(__FILE__).parent_path() / "../data";
  const std::filesystem::path model_path = base / (name + ".mat");
  return std::make_shared<MultiplicationModel>(model_path);
}
