#pragma once

#include <memory>
#include <relationship_graph.hpp>
#include <vector>

class RelationshipAnalyzer {
 public:
  RelationshipAnalyzer() = default;
  virtual std::shared_ptr<RelationshipGraph> Parse(std::string script) = 0;
  virtual std::vector<std::string> GetMutualFriends(std::string name1, std::string name2) = 0;

  virtual ~RelationshipAnalyzer() = default;
  RelationshipAnalyzer(const RelationshipAnalyzer &) = delete;
  RelationshipAnalyzer &operator=(const RelationshipAnalyzer &) = delete;
  RelationshipAnalyzer(RelationshipAnalyzer &&) = delete;
  RelationshipAnalyzer &operator=(RelationshipAnalyzer &&) = delete;
};
