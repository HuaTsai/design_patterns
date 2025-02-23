#include "video.hpp"

#include <format>
#include <iostream>

Video::Video(std::string title, std::string description, int length)
    : title_(title), description_(description), length_(length) {}

void Video::Like(std::string name) {
  std::cout << std::format("{} 對影片 \"{}\" 按讚。\n", name, title_);
}

std::string Video::title() const { return title_; }

std::string Video::description() const { return description_; }

int Video::length() const { return length_; }
