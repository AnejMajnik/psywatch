#include "components/cpu_data.hpp"
#include <chrono>
#include <ftxui/component/component.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/screen/string.hpp>
#include <memory>
#include <thread>
#include "util/file_io.hpp"

int main() {
    using namespace ftxui;

    std::string cpu_model = get_cpu_model();
    std::string cpu_temp = get_cpu_temp();

    auto screen = ScreenInteractive::Fullscreen();

    std::thread updater([&] () {
        while (true) {
            std::this_thread::sleep_for(std::chrono::seconds(1));
            cpu_temp = get_cpu_temp();
            screen.PostEvent(Event::Custom);
        }
    });

    auto cpu_data_base = std::make_shared<CpuData>(&cpu_model, &cpu_temp);

    auto component = Renderer(cpu_data_base, [cpu_data_base] {
        return cpu_data_base->Render();
    });


    screen.Loop(component);

    return 0;
}
