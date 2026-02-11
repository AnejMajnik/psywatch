#include <cstdio>
#include <sstream>
#include <string>
#include "get_cpu_data.hpp"
#include <bits/stdc++.h>
#include <fstream>

using namespace std;

string get_cpu_model() {
    string model_name = "CPU: ";

    ifstream file("/proc/cpuinfo");
    string line;
    string target = "model name";
    bool found = false;

    while(getline(file, line)) {
        if (line.find(target) != string::npos) {
            // If a ':' is found, extract after that
            size_t pos = string(line).find(':');
            model_name += string(line).substr(pos +2); // Skip colon and space

            return model_name;
        }
    }

    return model_name;
}

string get_cpu_temp() {
    string temperature = "Temperature: ";
    int temp = 0;

    ifstream file("/sys/class/hwmon/hwmon2/temp1_input");
    string line;

    getline(file, line);

    temp = stoi(line);
    temp /= 1000;

    temperature += to_string(temp);
    temperature += "˚C";

    return temperature;
}

string get_cpu_usage(std::deque<CpuUsage> &cpu_usage_log) {
    string usage = "Usage: ";

    ifstream file("/proc/stat");
    string line;

    getline(file, line);

    size_t pos = line.find("  ");
    string data = string(line).substr(pos + 2);

    CpuUsage currentUsage = parse_usage_stats(data);

    if (cpu_usage_log.size() < 2) {
        cpu_usage_log.push_back(currentUsage);
        return "Usage: ...";
    }

    CpuUsage previousUsage {};
    previousUsage = cpu_usage_log.back();
    usage += calculate_usage(previousUsage, currentUsage);
    usage += "%";

    cpu_usage_log.push_back(currentUsage);

    return usage;
}

CpuUsage parse_usage_stats(string line) {
    stringstream ss(line);
    string temp;

    // Separator
    char del = ' ';
    CpuUsage usage;

    vector<string> values;

    while (getline(ss, temp, del)) {
        values.push_back(temp);
    }

    for (int i=0; i<values.size()-1; i++) {
        switch (i) {
            case 0: {
                usage.user = stol(values[i]);
                break;
            }
            case 1: {
                usage.nice = stol(values[i]);
                break;
            }
            case 2: {
                usage.system = stol(values[i]);
                break;
            }
            case 3: {
                usage.idle = stol(values[i]);
                break;
            }
            case 4: {
                usage.iowait = stol(values[i]);
                break;
            }
            case 5: {
                usage.irq = stol(values[i]);
                break;
            }
            case 6: {
                usage.softirq = stol(values[i]);
                break;
            }
        }
    }

    return usage;
}

string calculate_usage(CpuUsage previousUsage, CpuUsage currentUsage) {
    long userDelta = currentUsage.user - previousUsage.user;
    long niceDelta = currentUsage.nice - previousUsage.nice;
    long systemDelta = currentUsage.system - previousUsage.system;
    long idleDelta = currentUsage.idle - previousUsage.idle;
    long iowaitDelta = currentUsage.iowait - previousUsage.iowait;
    long irqDelta = currentUsage.irq - previousUsage.irq;
    long softirqDelta = currentUsage.softirq - previousUsage.softirq;

    long totalDelta = userDelta + niceDelta + systemDelta + idleDelta + iowaitDelta + irqDelta + softirqDelta;

    long usage = ((totalDelta - idleDelta) * 100) / totalDelta;

    return to_string(usage);
}
