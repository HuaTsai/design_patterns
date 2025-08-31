#include <asciiui/asciiui.hpp>

int main() {
  auto ui = std::make_shared<ASCIIUI>(22, 13);
  ui->AddButton(3, 1, 1, 0, L"Hi, I miss u");
  ui->AddText(4, 4, L"Do u love me ?");
  ui->AddText(4, 5, L"Please tell...");
  ui->AddButton(3, 6, 1, 0, L"No");
  ui->AddButton(12, 6, 1, 0, L"Yes");
  ui->AddNumberedList(3, 9, {L"Let's Travel", L"Back to home", L"Have dinner"});
  ui->Show();  // Default: Basic ASCII Theme

  ui->SetTheme(Theme::kPrettyASCIITheme);
  ui->Show();

  ui->SetTheme(Theme::kBasicASCIITheme);
  ui->Show();
}