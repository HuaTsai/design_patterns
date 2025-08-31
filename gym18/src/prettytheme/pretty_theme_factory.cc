#include <prettytheme/pretty_button_renderer.hpp>
#include <prettytheme/pretty_numbered_list_renderer.hpp>
#include <prettytheme/pretty_text_renderer.hpp>
#include <prettytheme/pretty_theme_factory.hpp>

std::shared_ptr<NumberedListRenderer> PrettyThemeFactory::CreateNumberedListRenderer() {
  return std::make_shared<PrettyNumberedListRenderer>(ui());
}

std::shared_ptr<ButtonRenderer> PrettyThemeFactory::CreateButtonRenderer() {
  return std::make_shared<PrettyButtonRenderer>(ui());
}

std::shared_ptr<TextRenderer> PrettyThemeFactory::CreateTextRenderer() {
  return std::make_shared<PrettyTextRenderer>(ui());
}