#pragma once

#include <http_client.hpp>

class FakeHttpClient : public HttpClient {
 public:
  using HttpClient::HttpClient;
  std::vector<std::string> SendRequest(const std::vector<std::string> &urls) override;
};
