#pragma once

#include <http_client.hpp>
#include <memory>

class UrlProcessor : public HttpClient {
 public:
  explicit UrlProcessor(std::shared_ptr<HttpClient> next) : next_(next) {}

  std::vector<std::string> SendRequest(const std::vector<std::string> &urls) override = 0;

 protected:
  std::shared_ptr<HttpClient> next_;  // NOLINT
};
