#pragma once

#include <processor/url_processor.hpp>
#include <unordered_set>

class BlacklistUrlProcessor : public UrlProcessor {
 public:
  explicit BlacklistUrlProcessor(std::string filepath, std::shared_ptr<HttpClient> next);
  std::vector<std::string> SendRequest(const std::vector<std::string> &urls) override;

 private:
  std::unordered_set<std::string> blacklist_;
};
