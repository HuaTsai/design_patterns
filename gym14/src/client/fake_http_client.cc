#include <client/fake_http_client.hpp>

std::vector<std::string> FakeHttpClient::SendRequest(const std::vector<std::string> &urls) {
  if (urls.empty()) {
    return {};
  }
  return {"Hello World from " + urls[0]};
}
