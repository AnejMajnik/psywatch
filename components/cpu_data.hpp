#pragma once

#include <ftxui/component/component.hpp>
#include <ftxui/dom/elements.hpp>
#include <ftxui/screen/color.hpp>
#include <string>

using namespace ftxui;

class CpuData : public ComponentBase {
public:
    CpuData(std::string* cpu_model, std::string* cpu_temp, std::string* cpu_usage) : cpu_model_(cpu_model), cpu_temp_(cpu_temp), cpu_usage_(cpu_usage) {}

    Element Render() {
        return hbox({
            vbox(
                text(*cpu_model_)  | color(Color::Cyan1),
                text(*cpu_temp_)  | color(Color::Cyan1),
                text(*cpu_usage_) | color(Color::Cyan1)
            ),
            vbox(
            )
        }) | border | borderStyled(BorderStyle::EMPTY);
    }

private:
    std::string* cpu_model_;
    std::string* cpu_temp_;
    std::string* cpu_usage_;
};
