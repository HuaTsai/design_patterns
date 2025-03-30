#include <relationship_graph_impl.hpp>

RelationshipGraphImpl::RelationshipGraphImpl(std::shared_ptr<SuperRelationshipAnalyzer> analyzer)
    : analyzer_(analyzer) {}

bool RelationshipGraphImpl::HasConnection(std::string name1, std::string name2) {
  return analyzer_->HasConnection(name1, name2);
}
