#include <processor/load_balancing_url_processor.hpp>

LoadBalancingUrlProcessor::LoadBalancingUrlProcessor(std::shared_ptr<HttpClient> next)
    : UrlProcessor(next) {}

std::vector<std::string> LoadBalancingUrlProcessor::SendRequest(
    const std::vector<std::string> &urls) {
  if (urls.empty()) {
    return {};
  }

  auto ret = urls[++id_ % urls.size()];
  if (next_) {
    return next_->SendRequest({ret});
  }
  return {ret};
}
