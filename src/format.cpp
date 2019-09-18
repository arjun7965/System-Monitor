#include <string>

#include "format.h"

using std::string;

// INPUT: Long int measuring seconds
// OUTPUT: HH:MM:SS up * day
string Format::ElapsedTime(long time) {
  int day, hours, minutes, seconds;
  string uptime;

  // calculate day, hours, minutes and seconds
  // from the time (in secs) received from /proc/uptime
  day = (((time / 60) / 60) / 24);
  hours = (((time / 60) / 60) % 24);
  minutes = ((time / 60) % 60);
  seconds = time % 60;

  uptime = std::to_string(hours) + ":" + std::to_string(minutes) + ":"
           + std::to_string(seconds) + " up " + std::to_string(day) + " day";

  return uptime;
}

// INPUT: Long int measuring seconds
// OUTPUT: HH:MM:SS
string Format::Time(long time) {
  int hours, minutes, seconds;
  string uptime;

  // calculate hours, minutes and seconds
  // from the time received from /proc/[pid]/stat
  hours = (time / (60 * 60));
  minutes = ((time / 60) % 60);
  seconds = time % 60;

  uptime = std::to_string(hours) + ":" + std::to_string(minutes) + ":"
           + std::to_string(seconds);

  return uptime;
}
