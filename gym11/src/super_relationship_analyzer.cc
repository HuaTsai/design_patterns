#include <fstream>
#include <sstream>
#include <super_relationship_analyzer.hpp>

void SuperRelationshipAnalyzer::Init(const std::string &script) {
  std::ifstream ifs(script);
  if (!ifs) {
    throw std::runtime_error("Error opening input file");
  }

  std::string line;
  while (std::getline(ifs, line)) {
    std::stringstream ss(line);
    std::string nodea;
    std::string dash;
    std::string nodeb;
    ss >> nodea >> dash >> nodeb;
    if (dash != "--") {
      throw std::runtime_error("Invalid format: nodes must be separated by '--'");
    }
    union_find_.Union(nodea, nodeb);
    friends_[nodea].insert(nodeb);
  }

  ifs.close();
}

bool SuperRelationshipAnalyzer::IsMutualFriend(const std::string &target_name,
                                               const std::string &name1, const std::string &name2) {
  if (target_name == name1 || target_name == name2) {
    return false;
  }
  if (friends_.at(target_name).contains(name1) && friends_.at(target_name).contains(name2)) {
    return true;
  }
  return false;
}

bool SuperRelationshipAnalyzer::HasConnection(const std::string &name1, const std::string &name2) {
  return union_find_.IsConnected(name1, name2);
}
