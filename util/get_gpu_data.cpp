#include "get_gpu_data.hpp"
#include <cstdio>
#include <cstdlib>
#include <string>


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
