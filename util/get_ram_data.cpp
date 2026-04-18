#include "get_ram_data.hpp"
#include <cmath>
#include <fstream>
#include <iomanip>
#include <sstream>
#include <string>

using namespace std;

double get_total_ram() {
  double total_ram = 0;

  ifstream file("/proc/meminfo");
  string line = "";

  getline(file, line);

  stringstream ss(line);
  string throwaway_label;

  ss >> throwaway_label >> total_ram;

  return total_ram;
}

double get_available_ram() {
  double available_ram = 0;

  ifstream file("/proc/meminfo");
  string line = "";

  // Throwaway getline - need line 3
  for (int i = 0; i < 2; i++) {
    getline(file, line);
  }

  stringstream ss(line);
  string throwaway_label;

  ss >> throwaway_label >> available_ram;

  return available_ram;
}

string get_ram_usage() {
  double total = get_total_ram();
  double available = get_available_ram();

  double used = total - available;

  // Convert to GB
  total /= 1024 * 1024;
  used /= 1024 * 1024;

  // Truncate to leave 2 decimals
  double total_res = trunc(total*100)/100;
  double used_res = trunc(used*100)/100;

  string total_str;
  string used_str;

  stringstream ss;
  ss << fixed << setprecision(2) << total_res;
  total_str = ss.str();

  stringstream ss2;
  ss2 << fixed << setprecision(2) << used_res;
  used_str = ss2.str();

  string usage = "RAM usage: " + used_str + "/" + total_str + "GB";

  return usage;
}
