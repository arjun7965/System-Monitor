#include "processor.h"
#include "linux_parser.h"

using namespace std::chrono;

// Return the CPU utilization
float Processor::Utilization() {
  if (counter == 0) {
    time_ms = steady_clock::now();
    counter++;
  }
  long active_time = LinuxParser::ActiveJiffies();
  long idle_time = LinuxParser::IdleJiffies();
  long a_time = active_time - cached_active_time;
  long i_time = idle_time - cached_idle_time;
  long total_time = a_time + i_time;
  auto time_diff = duration_cast<std::chrono::milliseconds>(steady_clock::now() - time_ms);
  if (time_diff.count() > 100U) {
    cpu_utilization = (float) a_time / (float) total_time;
    cached_active_time = active_time;
    cached_idle_time = idle_time;
    time_ms = steady_clock::now();
    return cpu_utilization;
  }
  return cpu_utilization;
}
