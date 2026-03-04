#pragma once
#include <string>
#include "../structs/gpu_struct.hpp"
#include <deque>

using namespace std;

string get_gpu_temp();
string get_gpu_usage(deque<GpuUsage> &gpu_usage_log);
string get_total_vram();
string get_used_vram();
string build_vram_usage();
string get_power_draw();
