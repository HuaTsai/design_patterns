#include <file_models.hpp>
#include <print>
#include <thread>

namespace {
void PrintVector(const std::string &user, const std::array<float, 1000> &vector) {
  std::print("{} gets output[:5]: ", user);
  for (size_t i = 0; i < 5; ++i) {
    std::print("{} ", vector.at(i));
  }
  std::print("\n");
}
}  // namespace

int main() {
  auto t1 = std::thread([&]() {
    std::array<float, 1000> vector{};
    vector.fill(1.F);
    FileModels models1;
    std::print("User 1 creates Reflection model\n");
    auto model1 = models1.CreateModel("Reflection");
    std::print("User 1 calls linear transformation\n");
    auto res1 = model1->LinearTransformation(vector);
    PrintVector("user1", res1);
  });

  auto t2 = std::thread([&]() {
    std::array<float, 1000> vector{};
    vector.fill(1.F);
    FileModels models2;
    std::print("User 2 creates scaling model\n");
    auto model2 = models2.CreateModel("Scaling");
    std::print("User 2 calls linear transformation\n");
    auto res2 = model2->LinearTransformation(vector);
    PrintVector("user2", res2);
  });

  auto t3 = std::thread([&]() {
    std::array<float, 1000> vector{};
    vector.fill(1.F);
    FileModels models3;
    std::print("User 3 creates shrinking model\n");
    auto model3 = models3.CreateModel("Shrinking");
    std::print("User 3 calls linear transformation\n");
    auto res3 = model3->LinearTransformation(vector);
    PrintVector("user3", res3);
  });

  t1.join();
  t2.join();
  t3.join();
}
