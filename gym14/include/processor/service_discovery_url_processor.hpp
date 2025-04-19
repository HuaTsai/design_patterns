#pragma once

#include <processor/url_processor.hpp>
#include <unordered_map>

class ServiceDiscoveryUrlProcerssor : public UrlProcessor {
 public:
  explicit ServiceDiscoveryUrlProcerssor(std::string filepath, std::shared_ptr<HttpClient> next);
  std::vector<std::string> SendRequest(const std::vector<std::string> &urls) override;

 private:
  std::unordered_map<std::string, std::vector<std::string>> discover_lists_;
};
