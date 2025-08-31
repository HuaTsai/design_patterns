#pragma once

#include <asciiui/theme_factory.hpp>
#include <memory>

class PrettyThemeFactory : public ThemeFactory {
 public:
  using ThemeFactory::ThemeFactory;

  std::shared_ptr<NumberedListRenderer> CreateNumberedListRenderer() override;
  std::shared_ptr<ButtonRenderer> CreateButtonRenderer() override;
  std::shared_ptr<TextRenderer> CreateTextRenderer() override;
};