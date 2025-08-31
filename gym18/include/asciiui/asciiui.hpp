#pragma once

#include <asciiui/button.hpp>
#include <asciiui/numbered_list.hpp>
#include <asciiui/text.hpp>
#include <asciiui/theme.hpp>
#include <memory>
#include <vector>

class ThemeFactory;
class NumberedListRenderer;
class ButtonRenderer;
class TextRenderer;

class ASCIIUI : public std::enable_shared_from_this<ASCIIUI> {
 public:
  ASCIIUI(int width, int height);

  void SetTheme(Theme theme);
  void AddButton(int x, int y, int padding_h, int padding_v, const std::wstring &text);
  void AddNumberedList(int x, int y, const std::vector<std::wstring> &line_of_texts);
  void AddText(int x, int y, const std::wstring &text);
  void ClearData();
  void Show();

  const std::vector<std::wstring> &data() const { return data_; }
  std::vector<std::wstring> &data() { return data_; }

 private:
  int width_;
  int height_;
  Theme theme_{Theme::kBasicASCIITheme};
  std::vector<Button> buttons_;
  std::vector<NumberedList> numbered_lists_;
  std::vector<Text> texts_;
  std::vector<std::wstring> data_;
  std::shared_ptr<ThemeFactory> theme_factory_;
  std::shared_ptr<NumberedListRenderer> numbered_list_renderer_;
  std::shared_ptr<ButtonRenderer> button_renderer_;
  std::shared_ptr<TextRenderer> text_renderer_;
};