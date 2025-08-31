#include <asciiui/asciiui.hpp>
#include <asciiui/button_renderer.hpp>
#include <asciiui/numbered_list_renderer.hpp>
#include <asciiui/text_renderer.hpp>
#include <basictheme/basic_theme_factory.hpp>
#include <iostream>
#include <locale>
#include <prettytheme/pretty_theme_factory.hpp>
#include <print>

ASCIIUI::ASCIIUI(int width, int height) : width_(width), height_(height) {
  if (width_ < 1 || height_ < 1) {
    throw std::invalid_argument("Width and height must be positive");
  }
  std::locale::global(std::locale(""));
  std::wcout.imbue(std::locale());
  ClearData();
}

void ASCIIUI::AddButton(int x, int y, int padding_h, int padding_v, const std::wstring &text) {
  buttons_.emplace_back(x, y, padding_h, padding_v, text);
}

void ASCIIUI::AddNumberedList(int x, int y, const std::vector<std::wstring> &line_of_texts) {
  numbered_lists_.emplace_back(x, y, line_of_texts);
}

void ASCIIUI::AddText(int x, int y, const std::wstring &text) { texts_.emplace_back(x, y, text); }

void ASCIIUI::SetTheme(Theme theme) {
  if (theme_factory_ && theme_ == theme) {
    return;
  }

  switch (theme) {
    case Theme::kBasicASCIITheme:
      theme_factory_ = std::make_shared<BasicThemeFactory>(shared_from_this());
      theme_ = Theme::kBasicASCIITheme;
      break;
    case Theme::kPrettyASCIITheme:
      theme_factory_ = std::make_shared<PrettyThemeFactory>(shared_from_this());
      theme_ = Theme::kPrettyASCIITheme;
      break;
    default:
      throw std::runtime_error("Unknown theme");
  }

  numbered_list_renderer_ = theme_factory_->CreateNumberedListRenderer();
  button_renderer_ = theme_factory_->CreateButtonRenderer();
  text_renderer_ = theme_factory_->CreateTextRenderer();
}

void ASCIIUI::ClearData() {
  data_ = std::vector<std::wstring>(height_, std::wstring(width_, L' '));
  data_[0].assign(width_, L'.');
  for (int i = 1; i < height_ - 1; ++i) {
    data_[i][0] = L'.';
    data_[i][width_ - 1] = L'.';
  }
  data_[height_ - 1].assign(width_, L'.');
}

void ASCIIUI::Show() {
  if (!theme_factory_) {
    SetTheme(Theme::kBasicASCIITheme);
  }
  ClearData();
  for (const auto &button : buttons_) {
    button_renderer_->Show(button);
  }
  for (const auto &numbered_list : numbered_lists_) {
    numbered_list_renderer_->Show(numbered_list);
  }
  for (const auto &text : texts_) {
    text_renderer_->Show(text);
  }
  for (const auto &line : data_) {
    std::wcout << line << "\n";
  }
}
