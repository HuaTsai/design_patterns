#pragma once

#include <string>
#include <union_find.hpp>
#include <unordered_set>

class SuperRelationshipAnalyzer {
 public:
  void Init(std::string script);
  bool IsMutualFriend(std::string target_name, std::string name1, std::string name2);
  bool HasConnection(std::string name1, std::string name2);

 private:
  UnionFind union_find_;
  std::unordered_map<std::string, std::unordered_set<std::string>> friends_;
};
