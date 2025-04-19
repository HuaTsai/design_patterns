#pragma once

#include <string>
#include <vector>

class HttpClient {
 public:
  HttpClient() = default;

  virtual ~HttpClient() = default;
  HttpClient(const HttpClient &) = delete;
  HttpClient &operator=(const HttpClient &) = delete;
  HttpClient(HttpClient &&) = default;
  HttpClient &operator=(HttpClient &&) = default;

  virtual std::vector<std::string> SendRequest(const std::vector<std::string> &urls) = 0;
};
