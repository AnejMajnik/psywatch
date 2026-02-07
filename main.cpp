#include "components/cpu_data.hpp"
#include <chrono>
#include <deque>
#include <ftxui/component/component.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/screen/string.hpp>
#include <memory>
#include <thread>
#include "util/get_cpu_data.hpp"

int main() {
    using namespace ftxui;

    std::deque<CpuUsage> cpu_usage_log;

    std::string cpu_model = get_cpu_model();
    std::string cpu_temp = get_cpu_temp();
    std::string cpu_usage = get_cpu_usage(cpu_usage_log);

    auto screen = ScreenInteractive::Fullscreen();

    std::thread updater([&] () {
        while (true) {
            std::this_thread::sleep_for(std::chrono::seconds(1));
            cpu_temp = get_cpu_temp();
            cpu_usage = get_cpu_usage(cpu_usage_log);
            screen.PostEvent(Event::Custom);
        }
    });

    auto cpu_data_base = std::make_shared<CpuData>(&cpu_model, &cpu_temp, &cpu_usage);

    auto component = Renderer(cpu_data_base, [cpu_data_base] {
        return cpu_data_base->Render();
    });


    screen.Loop(component);

    return 0;
}
