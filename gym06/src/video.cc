#include "video.hpp"

#include <format>
#include <iostream>
#include <print>

Video::Video(const std::string &title, const std::string &description, int length)
    : title_(title), description_(description), length_(length) {}

void Video::Like(const std::string &name) { std::print("{} 對影片 \"{}\" 按讚。\n", name, title_); }

std::string Video::title() const { return title_; }

std::string Video::description() const { return description_; }

int Video::length() const { return length_; }
