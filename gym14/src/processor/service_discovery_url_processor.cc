#include <fstream>
#include <processor/service_discovery_url_processor.hpp>
#include <sstream>

ServiceDiscoveryUrlProcerssor::ServiceDiscoveryUrlProcerssor(std::string filepath,
                                                             std::shared_ptr<HttpClient> next)
    : UrlProcessor(next) {
  std::ifstream ifs(filepath);
  if (!ifs) {
    throw std::runtime_error("Failed to open discovery file: " + filepath);
  }

  std::string line;
  while (std::getline(ifs, line)) {
    const size_t colonPos = line.find(':');
    if (colonPos == std::string::npos) {
      continue;
    }

    std::string domain = line.substr(0, colonPos);
    std::string urllist = line.substr(colonPos + 1);

    domain.erase(0, domain.find_first_not_of(" \t\n\r"));
    domain.erase(domain.find_last_not_of(" \t\n\r") + 1);
    urllist.erase(0, urllist.find_first_not_of(" \t\n\r"));
    urllist.erase(urllist.find_last_not_of(" \t\n\r") + 1);

    std::istringstream ss(urllist);
    std::string url;

    while (std::getline(ss, url, ',')) {
      url.erase(0, url.find_first_not_of(" \t\n\r"));
      url.erase(url.find_last_not_of(" \t\n\r") + 1);
      discover_lists_[domain].emplace_back(url);
    }
  }
}

std::vector<std::string> ServiceDiscoveryUrlProcerssor::SendRequest(
    const std::vector<std::string> &urls) {
  if (urls.empty()) {
    return {};
  }

  size_t start = 0;
  if (urls[0].starts_with("http://")) {
    start = 7;
  } else if (urls[0].starts_with("https://")) {
    start = 8;
  } else {
    throw std::runtime_error("Invalid URL: " + urls[0]);
  }
  auto end = urls[0].find('/', start);
  auto domain = urls[0].substr(start, end - start);

  if (!discover_lists_.contains(domain)) {
    return {};
  }

  std::vector<std::string> ret;
  for (const auto &url : discover_lists_[domain]) {
    ret.emplace_back(urls[0].substr(0, start) + url + urls[0].substr(end));
  }

  if (next_) {
    return next_->SendRequest(ret);
  }
  return ret;
}
