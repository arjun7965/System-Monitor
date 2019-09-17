#include <unistd.h>
#include <cctype>
#include <sstream>
#include <string>
#include <vector>

#include "process.h"
#include "linux_parser.h"

using std::string;
using std::to_string;
using std::vector;

// TODO: Return this process's ID
int Process::Pid() { return 0; }

// Return the process's CPU utilization
float Process::CpuUtilization() const {
  return cpu_usageProcess;
}

// TODO: Return this process's CPU utilization
void Process::CpuUtilization(long active_ticks, long system_ticks) { }

// Return the command that generated this process
string Process::Command() {
  return LinuxParser::Command(Pid());
}

// TODO: Return this process's memory utilization
string Process::Ram() {
  return LinuxParser::Ram(Pid());
}

// TODO: Return the user (name) that generated this process
string Process::User() {
  return LinuxParser::User(Pid());
}

// TODO: Return the age of this process (in seconds)
long int Process::UpTime() { return 0; }

// Overload the "less than" comparison operator for Process objects
bool Process::operator<(Process const& a) const {
  return CpuUtilization() < a.CpuUtilization();
}

// Overload the "great than" comparison operator for Process objects
bool Process::operator>(Process const& a) const {
  return CpuUtilization() > a.CpuUtilization();
}