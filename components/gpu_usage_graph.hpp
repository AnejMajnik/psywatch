#pragma once
#include <ftxui/component/component.hpp>
#include <ftxui/component/component_base.hpp>
#include <ftxui/dom/canvas.hpp>
#include <ftxui/dom/elements.hpp>
#include "../structs/gpu_struct.hpp"

using namespace ftxui;

inline Component GpuUsageGraph(std::deque<GpuUsage> &usage) {
    return Renderer([&] {
        auto c = Canvas(200, 50);

        for (int i=0; i<usage.size(); i++) {
            int y1 = 0;
            int y2 = usage[i].usage/2;
            c.DrawPointLine(i, y1, i, y2, Color::Red1);
        }

        return vbox(
            text("GPU Usage"),
            canvas(std::move(c))
        ) | border | borderStyled(BorderStyle::EMPTY) | color(Color::Cyan1);
    });
}
