#include <cstdio>
#include <iostream>
#include <string>
#include <cstdlib>
#include "file_io.hpp"

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
