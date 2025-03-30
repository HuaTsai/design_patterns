#pragma once

#include <string>

class RelationshipGraph {
 public:
  RelationshipGraph() = default;
  virtual bool HasConnection(std::string name1, std::string name2) = 0;

  virtual ~RelationshipGraph() = default;
  RelationshipGraph(const RelationshipGraph &) = delete;
  RelationshipGraph &operator=(const RelationshipGraph &) = delete;
  RelationshipGraph(RelationshipGraph &&) = delete;
  RelationshipGraph &operator=(RelationshipGraph &&) = delete;
};
