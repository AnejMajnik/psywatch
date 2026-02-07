#include <cstdio>
#include <iostream>
#include <string>
#include <cstdlib>
#include "get_cpu_data.hpp"
#include <bits/stdc++.h>

using namespace std;

string get_cpu_model() {
    string model_name = "CPU: ";
    bool input = false;

    FILE* catPipe = popen("cat /proc/cpuinfo | grep 'model name' | head -n1", "r");

    if (catPipe == nullptr) {
        cerr << "Failed to run cat and grep" << endl;
        return "";
    }

    char buffer[128];
    while(fgets(buffer, sizeof(buffer), catPipe) != nullptr) {
        size_t pos = string(buffer).find(':');
        if (pos != string::npos) {
            // If a ':' is found, extract after that
            model_name += string(buffer).substr(pos +2); // Skip colon and space
            input = true;
        }

    }
    pclose(catPipe);
    return model_name;
}

string get_cpu_temp() {
    string temp = "Temperature: ";
    int sum = 0;
    int count = 0;

    FILE* catPipe = popen("cat /sys/class/hwmon/hwmon*/temp*_input", "r");

    char buffer[128];
    while(fgets(buffer, sizeof(buffer), catPipe) != nullptr) {
        sum += atoi(buffer);
        count++;
    }
    pclose(catPipe);

    int avgTemp = sum/1000/count;

    temp += to_string(avgTemp);
    temp += "˚C";

    return temp;
}

string get_cpu_usage(std::deque<CpuUsage> &cpu_usage_log) {
    string usage = "Usage: ";
    CpuUsage previousUsage {};

    if (!cpu_usage_log.empty()) {
        previousUsage = cpu_usage_log.back();
    }

    FILE* pipe = popen("head -n 1 /proc/stat | awk '{print $2, $3, $4, $5, $6, $7, $8}'", "r");

    char buffer[128];
    string line = "";

    while(fgets(buffer, sizeof(buffer), pipe) != nullptr) {
        line = buffer;
    }
    pclose(pipe);

    CpuUsage currentUsage = parse_usage_stats(line);

    usage += calculate_usage(previousUsage, currentUsage);
    usage += "%";

    cpu_usage_log.push_back(currentUsage);

    return usage;
}

CpuUsage parse_usage_stats(string line) {
    stringstream ss(line);

    // Temp string to store splitted string
    string temp;

    // Delimeter (seperator)
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
