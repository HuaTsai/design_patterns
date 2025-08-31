#include <basictheme/basic_button_renderer.hpp>
#include <basictheme/basic_numbered_list_renderer.hpp>
#include <basictheme/basic_text_renderer.hpp>
#include <basictheme/basic_theme_factory.hpp>

std::shared_ptr<NumberedListRenderer> BasicThemeFactory::CreateNumberedListRenderer() {
  return std::make_shared<BasicNumberedListRenderer>(ui());
}

std::shared_ptr<ButtonRenderer> BasicThemeFactory::CreateButtonRenderer() {
  return std::make_shared<BasicButtonRenderer>(ui());
}

std::shared_ptr<TextRenderer> BasicThemeFactory::CreateTextRenderer() {
  return std::make_shared<BasicTextRenderer>(ui());
}