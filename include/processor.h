#ifndef PROCESSOR_H
#define PROCESSOR_H

#include <chrono>
#include <iostream>

class Processor {
 public:
  float Utilization();                  // Return the CPU utilization of the system

 private:
  int counter{0};
  std::chrono::steady_clock::time_point time_ms;
  long cached_active_time{0};
  long cached_idle_time{0};
};

#endif
