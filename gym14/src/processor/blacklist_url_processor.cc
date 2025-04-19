#include <fstream>
#include <processor/blacklist_url_processor.hpp>
#include <sstream>

BlacklistUrlProcessor::BlacklistUrlProcessor(std::string filepath, std::shared_ptr<HttpClient> next)
    : UrlProcessor(next) {
  std::ifstream ifs(filepath);
  if (!ifs) {
    throw std::runtime_error("Failed to open blacklist file: " + filepath);
  }

  std::string line;
  while (std::getline(ifs, line)) {
    std::istringstream ss(line);
    std::string url;
    while (std::getline(ss, url, ',')) {
      url.erase(0, url.find_first_not_of(" \t\n\r"));
      url.erase(url.find_last_not_of(" \t\n\r") + 1);
      blacklist_.insert(url);
    }
  }
}

std::vector<std::string> BlacklistUrlProcessor::SendRequest(const std::vector<std::string> &urls) {
  for (const auto &url : urls) {
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

    if (blacklist_.contains(domain)) {
      throw std::runtime_error("URL is in blacklist: " + url);
    }
  }

  if (next_) {
    return next_->SendRequest(urls);
  }
  return urls;
}
