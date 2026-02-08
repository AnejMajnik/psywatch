#include "get_gpu_data.hpp"
#include <cstdio>
#include <cstdlib>
#include <string>
#include <cmath>
#include <iomanip>
#include <sstream>

using namespace std;

string get_gpu_temp() {
    string gpu_temp = "GPU temp: ";
    int temp = 0;
    FILE *pipe = popen("cat /sys/class/drm/card1/device/hwmon/hwmon1/temp1_input", "r");

    char buffer[128];
    while(fgets(buffer, sizeof(buffer), pipe) != nullptr) {
        temp = atoi(buffer);
    }
    fclose(pipe);

    temp /= 1000;
    gpu_temp += to_string(temp);
    gpu_temp += "°C";

    return gpu_temp;
}

string get_gpu_usage() {
    string gpu_usage = "GPU usage: ";
    int usage = 0;
    FILE *pipe = popen("cat /sys/class/drm/card1/device/gpu_busy_percent", "r");

    char buffer[128];
    while(fgets(buffer, sizeof(buffer), pipe) != nullptr) {
        usage = atoi(buffer);
    }
    fclose(pipe);

    gpu_usage += to_string(usage);
    gpu_usage += "%";

    return gpu_usage;
}



string get_total_vram() {
    string total_vram = "";
    double vram = 0;
    FILE *pipe = popen("cat /sys/class/drm/card1/device/mem_info_vram_total", "r");

    char buffer[128];
    while(fgets(buffer, sizeof(buffer), pipe) != nullptr) {
        vram = stod(buffer);
    }
    pclose(pipe);

    vram /= 1024*1024*1024;
    double result = trunc(vram * 100)/100; // Only use two decimals

    stringstream ss;
    ss << fixed << setprecision(2) << result;
    total_vram = ss.str();

    return total_vram;
}

string get_used_vram() {
    string used_vram = "";
    double vram = 0;
    FILE *pipe = popen("cat /sys/class/drm/card1/device/mem_info_vram_used", "r");

    char buffer[128];
    while(fgets(buffer, sizeof(buffer), pipe) != nullptr) {
        vram = stod(buffer);
    }
    pclose(pipe);

    vram /= 1024*1024*1024;
    double result = trunc(vram * 100)/100; // Only use two decimals

    stringstream ss;
    ss << fixed << setprecision(2) << result;
    used_vram = ss.str();

    return used_vram;
}

string build_vram_usage() {
    string total = get_total_vram();
    string used = get_used_vram();

    // Get usage %
    double usage = (stod(used)/stod(total))*100;

    string vram_usage = "VRAM usage: " + used + "/" + total + "GB " + "(" + to_string((int)usage) + "%)";

    return vram_usage;
}

string get_power_draw() {
    string power_draw = "Power: ";
    int usage = 0;
    FILE *pipe = popen("cat /sys/class/drm/card1/device/hwmon/hwmon1/power1_average", "r");

    char buffer[128];
    while(fgets(buffer, sizeof(buffer), pipe) != nullptr) {
        usage = atoi(buffer);
    }
    pclose(pipe);

    usage /= 1000000;
    power_draw += to_string(usage);
    power_draw += "W";

    return power_draw;
}
