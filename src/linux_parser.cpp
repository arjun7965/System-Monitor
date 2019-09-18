#include <dirent.h>
#include <unistd.h>
#include <string>
#include <vector>

#include "linux_parser.h"

using std::stof;
using std::string;
using std::to_string;
using std::vector;

//---------------*************************************************------------------------------
// --------------Helper functions for System class starts from here------------------------------

// Read and return the operating system name
string LinuxParser::OperatingSystem() {
  string line;
  string key;
  string value;
  std::ifstream filestream(kOSPath);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::replace(line.begin(), line.end(), ' ', '_');
      std::replace(line.begin(), line.end(), '=', ' ');
      std::replace(line.begin(), line.end(), '"', ' ');
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "PRETTY_NAME") {
          std::replace(value.begin(), value.end(), '_', ' ');
          return value;
        }
      }
    }
  }
  return value;
}

// Read and return the kernel version
string LinuxParser::Kernel() {
  string os, version, kernel;
  string line;
  std::ifstream stream(kProcDirectory + kVersionFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> os >> version >> kernel;
  }
  return kernel;
}

// TODO: Update this to use std::filesystem
vector<int> LinuxParser::Pids() {
  vector<int> pids;
  DIR* directory = opendir(kProcDirectory.c_str());
  struct dirent* file;
  while ((file = readdir(directory)) != nullptr) {
    // Is this a directory?
    if (file->d_type == DT_DIR) {
      // Is every character of the name a digit?
      string filename(file->d_name);
      if (std::all_of(filename.begin(), filename.end(), isdigit)) {
        int pid = stoi(filename);
        pids.push_back(pid);
      }
    }
  }
  closedir(directory);
  return pids;
}

// Read and return the system memory utilization
float LinuxParser::MemoryUtilization() {
  long MemTotal, MemFree, Buffers, Cached;
  string line, key, value;
  std::ifstream filestream(kProcDirectory + kMeminfoFilename);
  if(filestream.is_open()) {
    while(std::getline(filestream, line)) {
      std::istringstream stream(line);
      while(stream >> key >> value) {
        if (key == "MemTotal:") {
          MemTotal = stol(value);
        } else if (key == "MemFree:") {
          MemFree = stol(value);
        } else if (key == "Cached:") {
          Cached = stol(value);
        }
      }
    }
  }
  long MemUsed = MemTotal - MemFree - Cached;
  return (float) MemUsed / MemTotal;
}

// Read and return the system uptime
long LinuxParser::UpTime() {
  long int uptime;
  string line, value;
  std::ifstream filestream(kProcDirectory + kUptimeFilename);
  if(filestream.is_open()) {
    std::getline(filestream, line);
    std::istringstream stream(line);
    if(stream >> value) {
      uptime = stol(value);
    }
  }
  return uptime;
}

// Read and return the total number of processes
int LinuxParser::TotalProcesses() {
  int numProcesses;
  string line, key, value;
  std::ifstream filestream(kProcDirectory + kStatFilename);
  if(filestream.is_open()) {
    while(std::getline(filestream, line)) {
      std::istringstream stream(line);
      while(stream >> key >> value) {
        if(key == "processes") {
          numProcesses = stoi(value);
        }
      }
    }
  }
  return numProcesses;
}

// Read and return the number of running processes
int LinuxParser::RunningProcesses() {
  int runProcesses;
  string line, key, value;
  std::ifstream filestream(kProcDirectory + kStatFilename);
  if(filestream.is_open()) {
    while(std::getline(filestream, line)) {
      std::istringstream stream(line);
      while(stream >> key >> value) {
        if(key == "procs_running") {
          runProcesses = stoi(value);
        }
      }
    }
  }
  return runProcesses;
}
// Read and return the number of jiffies for the system
long LinuxParser::Jiffies() {
  return UpTime() * sysconf(_SC_CLK_TCK);
}

//---------------*************************************************-------------------------------
// --------------Helper functions for Processor class starts from here------------------------------

// Read and return the number of active jiffies for the system
long LinuxParser::ActiveJiffies() {
  vector<string> time = CpuUtilization();
  return (stol(time[CPUStates::kUser_]) + stol(time[CPUStates::kNice_]) +
          stol(time[CPUStates::kSystem_]) + stol(time[CPUStates::kIRQ_]) +
          stol(time[CPUStates::kSoftIRQ_]) + stol(time[CPUStates::kSteal_]));
}

// Read and return the number of idle jiffies for the system
long LinuxParser::IdleJiffies() {
  vector<string> time = CpuUtilization();
  return (stol(time[CPUStates::kIdle_]) + stol(time[CPUStates::kIOwait_]));
}

// Read and return CPU utilization
vector<string> LinuxParser::CpuUtilization() {
  vector<string> utilization;
  string line, value;
  std::ifstream filestream(kProcDirectory + kStatFilename);
  if (filestream.is_open()) {
    std::getline(filestream, line);
    std::istringstream stream(line);
    if (stream >> value) {
      if (value == "cpu") {
        while (stream >> value)
          utilization.push_back(value);
      }
    }
  }
  return utilization;
}

//---------------*************************************************------------------------------
// --------------Helper functions for Process class starts from here------------------------------

// Read and return the number of active jiffies for a PID
long LinuxParser::ActiveJiffies(int pid) {
  string line, token;
  vector<string> values;
  std::ifstream filestream(kProcDirectory + std::to_string(pid) + kStatFilename);
  if (filestream.is_open()) {
    std::getline(filestream, line);
    std::istringstream stream(line);
    while (stream >> token) {
      values.push_back(token);
    }
  }
  long utime = stol(values[13]);
  long stime = stol(values[14]);
  long cutime = stol(values[15]);
  long cstime = stol(values[16]);
  long total_time = utime + stime + cutime + cstime;
  return total_time;
}

// Read and return the command associated with a process
string LinuxParser::Command(int pid) {
  string line;
  std::ifstream filestream(kProcDirectory + std::to_string(pid) + kCmdlineFilename);
  if (filestream.is_open()) {
    std::getline(filestream,line);
    return line;
  }
  return string("");
}

// Read and return the memory used by a process
string LinuxParser::Ram(int pid) {
  string line, key, value;
  std::ifstream filestream(kProcDirectory + std::to_string(pid) + kStatusFilename);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::istringstream stream(line);
      while(stream >> key >> value) {
        if (key == "VmSize:") {
          return std::to_string(stol(value) / 1024);
        }
      }
    }
  }
  return string("0");
}

// Read and return the user ID associated with a process
string LinuxParser::Uid(int pid) {
  string line, key, value;
  std::ifstream filestream(kProcDirectory + std::to_string(pid) + kStatusFilename);
  if (filestream.is_open()) {
    while (getline(filestream, line)) {
      std::istringstream stream(line);
      while (stream >> key >> value) {
        if (key == "Uid:") {
          return value;
        }
      }
    }
  }
  return value;
}

// Read and return the user associated with a process
string LinuxParser::User(int pid) {
  string value1, value2, value3, line;
  std::ifstream filestream(kPasswordPath);
  if (filestream.is_open()) {
    while (getline(filestream, line)) {
      std::replace(line.begin(), line.end(), ':', ' ');
      std::istringstream stream(line);
      while (stream >> value1 >> value2 >> value3) {
        if (value2 == "x" && value3 == Uid(pid)) {
          return value1;
        }
      }
    }
  }
  return "";
}

// Read and return the uptime of a process
long LinuxParser::UpTime(int pid) {
  string line, value;
  int counter = -1;
  long uptime;
  std::ifstream filestream(kProcDirectory + std::to_string(pid) + kStatFilename);
  if (filestream.is_open()) {
    std::getline(filestream, line);
    std::istringstream stream(line);
    while (stream >> value){
      counter++;
      if (counter == 21) {
        uptime = stol(value) / sysconf(_SC_CLK_TCK);
        return uptime;
      }
    }
  }
  return 0;
}
