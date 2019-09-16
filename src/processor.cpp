#include "processor.h"
#include "linux_parser.h"

// Return the aggregate CPU utilization
float Processor::Utilization() {
  long active_time = LinuxParser::ActiveJiffies();
  long idle_time = LinuxParser::IdleJiffies();
  long total_time = active_time + idle_time;
  float cpu_utilization = static_cast<float> (active_time / total_time * 100);
  return cpu_utilization;
}