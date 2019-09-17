#include "processor.h"
#include "linux_parser.h"


// Return the aggregate CPU utilization
float Processor::Utilization() {
  float cpu_utilization;
  long active_time = LinuxParser::ActiveJiffies();
  long idle_time = LinuxParser::IdleJiffies();
  long a_time = active_time - cached_active_time;
  long i_time = idle_time - cached_idle_time;
  long total_time = a_time + i_time;
  cpu_utilization = (float) a_time / (float) total_time;
  cached_active_time = active_time;
  cached_idle_time = idle_time;
  return cpu_utilization;
}
