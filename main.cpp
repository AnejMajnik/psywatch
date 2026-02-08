#include "components/cpu_data.hpp"
#include <chrono>
#include <deque>
#include <ftxui/component/component.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/screen/string.hpp>
#include <memory>
#include <thread>
#include "components/gpu_data.hpp"
#include "util/get_cpu_data.hpp"
#include "util/get_gpu_data.hpp"

int main() {
    using namespace ftxui;

    std::deque<CpuUsage> cpu_usage_log;

    // CPU
    std::string cpu_model = get_cpu_model();
    std::string cpu_temp = get_cpu_temp();
    std::string cpu_usage = get_cpu_usage(cpu_usage_log);

    // GPU
    std::string gpu_temp = get_gpu_temp();
    std::string gpu_usage = get_gpu_usage();
    std::string vram_usage = build_vram_usage();


    auto screen = ScreenInteractive::Fullscreen();

    std::thread updater([&] () {
        while (true) {
            std::this_thread::sleep_for(std::chrono::milliseconds(750));

            // CPU
            cpu_temp = get_cpu_temp();
            cpu_usage = get_cpu_usage(cpu_usage_log);

            // GPU
            gpu_temp = get_gpu_temp();
            gpu_usage = get_gpu_usage();
            vram_usage = build_vram_usage();

            screen.PostEvent(Event::Custom);
        }
    });

    auto cpu_data_base = std::make_shared<CpuData>(&cpu_model, &cpu_temp, &cpu_usage);
    auto gpu_data_base = std::make_shared<GpuData>(&gpu_temp, &gpu_usage, &vram_usage);

    auto container = Container::Vertical({
        cpu_data_base,
        gpu_data_base
    });

    auto renderer = Renderer(container, [&] {
        return vbox({
            cpu_data_base->Render(),
            gpu_data_base->Render()
        });
    });


    screen.Loop(renderer);

    return 0;
}
