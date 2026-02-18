#pragma once

#include <ftxui/component/component.hpp>
#include <ftxui/dom/elements.hpp>
#include <ftxui/screen/color.hpp>
#include <string>

using namespace ftxui;

inline Component CpuData(const std::string &cpu_model, const std::string &cpu_temp, const std::string &cpu_usage) {
    return Renderer([&] {
        return vbox(
            text(cpu_model) | color(Color::Cyan1),
            text(cpu_temp) | color(Color::Cyan1),
            text(cpu_usage) | color(Color::Cyan1)
        ) | border | borderStyled(BorderStyle::EMPTY) | color(Color::Cyan1);
    });
};
