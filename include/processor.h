#ifndef PROCESSOR_H
#define PROCESSOR_H

class Processor {
 public:
  float Utilization();                  // Return the CPU utilization of the system

 private:
  long cached_active_time{0};
  long cached_idle_time{0};
};

#endif
