#pragma once

#include <ftxui/component/component.hpp>
#include <ftxui/component/component_base.hpp>
#include <ftxui/dom/elements.hpp>

using namespace ftxui;

class GpuData : public ComponentBase {
public:
    GpuData(std::string *gpu_temp, std::string *gpu_usage, std::string *vram_usage) : gpu_temp_(gpu_temp), gpu_usage_(gpu_usage), vram_usage_(vram_usage) {}

    Element Render() {
        return vbox(
            text(*gpu_temp_) | color(Color::HotPink2),
            text(*gpu_usage_) | color(Color::HotPink2),
            text(*vram_usage_) | color(Color::HotPink2)
        ) | border | borderStyled(BorderStyle::EMPTY);
    }


private:
    std::string* gpu_temp_;
    std::string* gpu_usage_;
    std::string* vram_usage_;
};
