#pragma once

#include <string>
#include <union_find.hpp>
#include <unordered_set>

class SuperRelationshipAnalyzer {
 public:
  void Init(const std::string& script);
  bool IsMutualFriend(const std::string& target_name, const std::string& name1, const std::string& name2);
  bool HasConnection(const std::string& name1, const std::string& name2);

 private:
  UnionFind union_find_;
  std::unordered_map<std::string, std::unordered_set<std::string>> friends_;
};
