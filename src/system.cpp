#include <unistd.h>
#include <cstddef>
#include <set>
#include <string>
#include <vector>

#include "process.h"
#include "processor.h"
#include "system.h"
#include "linux_parser.h"

using std::set;
using std::size_t;
using std::string;
using std::vector;

// TODO: Return the system's CPU
Processor& System::Cpu() { return cpu_; }

// Return a container composed of the system's processes
vector<Process>& System::Processes() {
  vector<int> pids = LinuxParser::Pids();

  // create a set of existing pid's
  // we use std::set so the processes are in order 
  set<int>existing_pids;
  for (Process& process : processes_) {
    existing_pids.insert(process.Pid());
  }

  // add all the new processes
  for (int p : pids) {
    if (existing_pids.find(p) == existing_pids.end())
      processes_.emplace_back(p);
  }

  // update the CPU utilization
  for (auto& process : processes_) {
    process.CpuUtilization(LinuxParser::ActiveJiffies(process.Pid()),
                          LinuxParser::Jiffies());
  }
  std::sort(processes_.begin(), processes_.end(), std::greater<Process>());
  return processes_;
}

// Return the system's kernel identifier (string)
std::string System::Kernel() {
  if(kernel.empty()) {
    kernel = LinuxParser::Kernel();
  }
  return kernel;
}

// Return the system's memory utilization
float System::MemoryUtilization() {
  return LinuxParser::MemoryUtilization();
}

// Return the operating system name
std::string System::OperatingSystem() {
  if(OS.empty()) {
    OS = LinuxParser::OperatingSystem();
  }
  return OS;
}

// Return the number of processes actively running on the system
int System::RunningProcesses() {
  return LinuxParser::RunningProcesses();
}

// Return the total number of processes on the system
int System::TotalProcesses() {
  return LinuxParser::TotalProcesses();
}

// Return the number of seconds since the system started running
long int System::UpTime() {
  return LinuxParser::UpTime();
}
