#pragma once

#include <ftxui/component/component.hpp>
#include <ftxui/component/component_base.hpp>
#include <ftxui/dom/elements.hpp>

using namespace ftxui;

inline Component RamData(std::string &ram_usage) {
  return Renderer([&] {
    return vbox(text(ram_usage) | color(Color::RGB(255, 171, 241))) | border |
           borderStyled(BorderStyle::EMPTY) | color(Color::RGB(255, 171, 241));
  });
}
