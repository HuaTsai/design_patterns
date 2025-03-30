#pragma once

#include <memory>
#include <relationship_graph.hpp>
#include <super_relationship_analyzer.hpp>

class RelationshipGraphImpl : public RelationshipGraph {
 public:
  explicit RelationshipGraphImpl(std::shared_ptr<SuperRelationshipAnalyzer> analyzer);

  bool HasConnection(std::string name1, std::string name2) override;

 private:
  std::shared_ptr<SuperRelationshipAnalyzer> analyzer_;
};
