#pragma once

#include <relationship_analyzer.hpp>
#include <super_relationship_analyzer.hpp>
#include <unordered_set>

class SuperRelationshipAnalyzerAdapter : public RelationshipAnalyzer {
 public:
  std::shared_ptr<RelationshipGraph> Parse(const std::string &script) override;
  std::vector<std::string> GetMutualFriends(const std::string &name1,
                                            const std::string &name2) override;

 private:
  std::shared_ptr<SuperRelationshipAnalyzer> analyzer_;
  std::unordered_set<std::string> names_;
};
