#pragma once

#include <ftxui/component/component.hpp>
#include <ftxui/component/component_base.hpp>
#include <ftxui/dom/elements.hpp>

using namespace ftxui;

inline Component GpuData(std::string &gpu_temp, std::string &gpu_usage, std::string &vram_usage, std::string &power_draw) {
    return Renderer([&] {
        return vbox(
            text(gpu_temp) | color(Color::RGB(150, 0, 255)),
            text(gpu_usage) | color(Color::RGB(150, 0, 255)),
            text(vram_usage) | color(Color::RGB(150, 0, 255)),
            text(power_draw) | color(Color::RGB(150, 0, 255))
        ) | border | borderStyled(BorderStyle::EMPTY) | color(Color::RGB(150, 0, 255));
    });
}
