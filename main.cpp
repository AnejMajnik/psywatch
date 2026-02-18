#include "components/cpu_data.hpp"
#include <chrono>
#include <deque>
#include <ftxui/component/component.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/screen/string.hpp>
#include <thread>
#include "components/gpu_data.hpp"
#include "util/get_cpu_data.hpp"
#include "util/get_gpu_data.hpp"
#include <cmath>

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
    std::string power_draw = get_power_draw();


    auto screen = ScreenInteractive::Fullscreen();
    float time = 0;

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
            power_draw = get_power_draw();

            time += 0.016f;

            screen.PostEvent(Event::Custom);
        }
    });

    auto cpu_data_component = CpuData(cpu_model, cpu_temp, cpu_usage);
    auto gpu_data_component = GpuData(gpu_temp, gpu_usage, vram_usage, power_draw);

    auto container = Container::Vertical({
        cpu_data_component,
        gpu_data_component
    });

    auto renderer = Renderer(container, [&] {
        auto c = Canvas(200, 200);

        int x = 100 + (int)(80 * cos(time * 2));
        int y = 50 + (int)(40 * sin(time * 3));

        c.DrawPointCircleFilled(x, y, 10, Color::Cyan);
        return vbox({
            cpu_data_component->Render(),
            gpu_data_component->Render(),
            canvas(std::move(c))
        });
    });


    screen.Loop(renderer);

    return 0;
}
