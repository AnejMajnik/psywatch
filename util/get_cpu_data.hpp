#pragma once
#include <string>
#include "../structs/cpu_struct.hpp"
#include <deque>

using namespace std;

string get_cpu_model();
string get_cpu_temp();
string get_cpu_usage(deque<RawCpuUsage> &raw_cpu_usage_log, deque<CpuUsage> &cpu_usage_log);
RawCpuUsage parse_usage_stats(string line);
string calculate_usage(RawCpuUsage previousUsage, RawCpuUsage currentUsage);
