#pragma once

#include <ftxui/component/component.hpp>
#include <ftxui/dom/elements.hpp>
#include <ftxui/screen/color.hpp>
#include <string>

using namespace ftxui;

class CpuData : public ComponentBase {
public:
    CpuData(std::string* cpu_model, std::string* cpu_temp) : cpu_model_(cpu_model), cpu_temp_(cpu_temp) {}

    Element Render() {
        return hbox({
            vbox(
                text(*cpu_model_)  | color(Color::Cyan1),
                text(*cpu_temp_)  | color(Color::Cyan1)
            ) | border | color(Color::Pink1),
            vbox(
                text("Hello from screen 2") | color(Color::HotPink2)
            )
        }) | border | color(Color::Cyan1) | size(HEIGHT, EQUAL, 100);
    }

private:
    std::string* cpu_model_;
    std::string* cpu_temp_;
};
