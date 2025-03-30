#pragma once

#include <string>
#include <unordered_map>

class UnionFind {
 public:
  void Union(std::string p, std::string q);
  bool IsConnected(std::string p, std::string q);
  std::string Find(std::string p);

 private:
  void InitParentIfEmpty(std::string p);
  std::unordered_map<std::string, std::string> parent_;
};
