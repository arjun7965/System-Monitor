#ifndef PROCESS_H
#define PROCESS_H

#include <string>
/*
Basic class for Process representation
It contains relevant attributes as shown below
*/
class Process {
 public:
  Process(int pid) : pid_(pid) {}
  int Pid();
  std::string User();
  std::string Command();
  float CpuUtilization() const;
  void CpuUtilization(long active_ticks, long system_ticks);
  std::string Ram();
  long int UpTime();
  bool operator<(Process const& a) const;
  bool operator>(Process const& a) const;

 private:
  int pid_;
  float cpu_usageProcess{0};
  long cached_active_ticks{0};
  long cached_system_ticks{0};
};

#endif
