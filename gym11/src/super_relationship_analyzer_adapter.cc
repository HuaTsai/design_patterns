#include <filesystem>
#include <fstream>
#include <relationship_graph_impl.hpp>
#include <sstream>
#include <super_relationship_analyzer_adapter.hpp>

std::shared_ptr<RelationshipGraph> SuperRelationshipAnalyzerAdapter::Parse(std::string script) {
  std::ifstream ifs(script);
  if (!ifs) {
    throw std::runtime_error("Error opening input file");
  }

  const std::string tmp_file = "/tmp/script.txt";
  std::ofstream ofs(tmp_file);
  if (!ofs) {
    throw std::runtime_error("Error opening output file");
  }

  std::string line;
  while (std::getline(ifs, line)) {
    std::stringstream ss(line);
    std::string nodea;
    ss >> nodea;
    if (nodea.back() != ':') {
      throw std::runtime_error("Invalid format: node name must end with ':'");
    }
    nodea.pop_back();
    names_.insert(nodea);

    std::string nodeb;
    while (ss >> nodeb) {
      std::print(ofs, "{} -- {}\n", nodea, nodeb);
      names_.insert(nodeb);
    }
  }

  ifs.close();
  ofs.close();

  analyzer_ = std::make_shared<SuperRelationshipAnalyzer>();
  analyzer_->Init(tmp_file);
  std::filesystem::remove(tmp_file);

  return std::make_shared<RelationshipGraphImpl>(analyzer_);
}

std::vector<std::string> SuperRelationshipAnalyzerAdapter::GetMutualFriends(std::string name1,
                                                                            std::string name2) {
  std::vector<std::string> ret;
  for (const auto &name : names_) {
    if (name == name1 || name == name2) {
      continue;
    }
    if (analyzer_->IsMutualFriend(name, name1, name2)) {
      ret.emplace_back(name);
    }
  }
  return ret;
}
