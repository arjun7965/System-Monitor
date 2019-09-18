#ifndef SYSTEM_H
#define SYSTEM_H

#include <string>
#include <vector>

#include "process.h"
#include "processor.h"

class System {
 public:
  Processor& Cpu();                   // Return the processor object
  std::vector<Process>& Processes();  // Return a container composed of the system's processes
  float MemoryUtilization();          // Return the memory utilization of the system
  long UpTime();                      // Return the uptime of the system
  int TotalProcesses();               // Return the total number of processes
  int RunningProcesses();             // Return the number of processes actively running
  std::string Kernel();               // Return the kernel version
  std::string OperatingSystem();      // Return the Operating system name

 private:
  Processor cpu_;                     // Processor object
  std::vector<Process> processes_;    // container to store the processes running on the system
  std::string OS, kernel;             // variables to store OS & kernel strings
};

#endif
