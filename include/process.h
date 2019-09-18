#ifndef PROCESS_H
#define PROCESS_H

#include <string>
/*
Basic class for Process representation
It contains relevant attributes as shown below
*/
class Process {
 public:
  Process(int pid) : pid_(pid) {}                                 // Processor constructor
  int Pid();
  std::string User();                                             // return the username who started the process
  std::string Command();                                          // return the command taht kicked off the process
  float CpuUtilization() const;                                   // return the cpu utilization of the process
  void CpuUtilization(long active_ticks, long system_ticks);      // calculates the cpu utilization of the process
  std::string Ram();                                              // returns the memory utlization of the process
  long int UpTime();                                              // return the uptime of a process
  bool operator<(Process const& a) const;                         // overload 'less than' operator
  bool operator>(Process const& a) const;                         // overload 'great than' operator

 private:
  int pid_;
  float cpu_usageProcess{0};                                      // variable that stores the cpu utilization of a process
  long cached_active_ticks{0};                                    // variable to store active_ticks of the previous cpu cycle 
  long cached_system_ticks{0};                                    // variable to store system_ticks of the previous cpu cycle
};

#endif
