#include <print>
#include <super_relationship_analyzer_adapter.hpp>

int main() {
  auto adapter = std::make_shared<SuperRelationshipAnalyzerAdapter>();
  auto graph = adapter->Parse("gym11/data/script.txt");

  auto fs1 = adapter->GetMutualFriends("A", "B");
  std::print("Mutual friends of A and B: ");
  for (const auto &f : fs1) {
    std::print("{} ", f);
  }
  std::println();

  auto fs2 = adapter->GetMutualFriends("A", "C");
  std::print("Mutual friends of A and C: ");
  for (const auto &f : fs2) {
    std::print("{} ", f);
  }
  std::println();

  auto fs3 = adapter->GetMutualFriends("C", "D");
  std::print("Mutual friends of C and D: ");
  for (const auto &f : fs3) {
    std::print("{} ", f);
  }
  std::println();

  auto con1 = graph->HasConnection("A", "B");
  std::print("A and B are connected: {}\n", con1);

  auto con2 = graph->HasConnection("B", "M");
  std::print("B and M are connected: {}\n", con2);

  auto con3 = graph->HasConnection("B", "Z");
  std::print("B and Z are connected: {}\n", con3);
}
