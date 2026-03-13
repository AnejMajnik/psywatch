#include "components/cpu_data.hpp"
#include <chrono>
#include <deque>
#include <ftxui/component/component.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/screen/string.hpp>
#include <thread>
#include "components/gpu_data.hpp"
#include "components/gpu_usage_graph.hpp"
#include "components/cpu_usage_graph.hpp"
#include "structs/gpu_struct.hpp"
#include "util/get_cpu_data.hpp"
#include "util/get_gpu_data.hpp"
#include <cmath>
#include "util/util.hpp"

int main() {
    using namespace ftxui;

    // For calculations
    std::deque<RawCpuUsage> raw_cpu_usage_log;

    // Graph
    std::deque<CpuUsage> cpu_usage_log;
    std::deque<GpuUsage> gpu_usage_log;

    // CPU
    std::string cpu_model = get_cpu_model();
    std::string cpu_temp = get_cpu_temp();
    std::string cpu_usage = get_cpu_usage(raw_cpu_usage_log, cpu_usage_log);

    // GPU
    std::string gpu_temp = get_gpu_temp();
    std::string gpu_usage = get_gpu_usage(gpu_usage_log);
    std::string vram_usage = build_vram_usage();
    std::string power_draw = get_power_draw();


    auto screen = ScreenInteractive::Fullscreen();
    float time = 0;

    std::thread updater([&] () {
        while (true) {
            std::this_thread::sleep_for(std::chrono::milliseconds(750));

            // CPU
            cpu_temp = get_cpu_temp();
            cpu_usage = get_cpu_usage(raw_cpu_usage_log, cpu_usage_log);

            // GPU
            gpu_temp = get_gpu_temp();
            gpu_usage = get_gpu_usage(gpu_usage_log);
            vram_usage = build_vram_usage();
            power_draw = get_power_draw();

            Util::trim_usage_deque(cpu_usage_log);
            Util::trim_usage_deque(gpu_usage_log);

            time += 0.016f;

            screen.PostEvent(Event::Custom);
        }
    });

    auto cpu_data_component = CpuData(cpu_model, cpu_temp, cpu_usage);
    auto gpu_data_component = GpuData(gpu_temp, gpu_usage, vram_usage, power_draw);
    auto graph_gpu_component = GpuUsageGraph(gpu_usage_log);
    auto graph_cpu_component = CpuUsageGraph(cpu_usage_log);

    auto container = Container::Vertical({
        cpu_data_component,
        graph_cpu_component,
        gpu_data_component,
        graph_gpu_component,
    });

    auto renderer = Renderer(container, [&] {
        return vbox({
            cpu_data_component->Render(),
            graph_cpu_component->Render(),
            gpu_data_component->Render(),
            graph_gpu_component->Render(),
        });
    });


    screen.Loop(renderer);

    return 0;
}
