#pragma once

#include <string>

class Video {
 public:
  explicit Video(std::string title, std::string description, int length);
  void Like(std::string name);

  std::string title() const;
  std::string description() const;
  int length() const;

 private:
  std::string title_;
  std::string description_;
  int length_;
};
