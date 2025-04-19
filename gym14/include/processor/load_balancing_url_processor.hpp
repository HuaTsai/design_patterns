#pragma once

#include <processor/url_processor.hpp>

class LoadBalancingUrlProcessor : public UrlProcessor {
 public:
  explicit LoadBalancingUrlProcessor(std::shared_ptr<HttpClient> next);
  std::vector<std::string> SendRequest(const std::vector<std::string> &urls) override;

 private:
  int id_ = -1;
};
