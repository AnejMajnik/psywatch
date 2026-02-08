#pragma once

#include <ftxui/component/component.hpp>
#include <ftxui/component/component_base.hpp>
#include <ftxui/dom/elements.hpp>

using namespace ftxui;

class GpuData : public ComponentBase {
public:
    GpuData(std::string *gpu_temp, std::string *gpu_usage, std::string *vram_usage, std::string *power_draw) : gpu_temp_(gpu_temp), gpu_usage_(gpu_usage), vram_usage_(vram_usage), power_draw_(power_draw) {}

    Element Render() {
        return vbox(
            text(*gpu_temp_) | color(Color::RGB(150, 0, 255)),
            text(*gpu_usage_) | color(Color::RGB(150, 0, 255)),
            text(*vram_usage_) | color(Color::RGB(150, 0, 255)),
            text(*power_draw_) | color(Color::RGB(150, 0, 255))
        ) | border | borderStyled(BorderStyle::EMPTY) | color(Color::RGB(150, 0, 255));
    }


private:
    std::string* gpu_temp_;
    std::string* gpu_usage_;
    std::string* vram_usage_;
    std::string* power_draw_;
};
