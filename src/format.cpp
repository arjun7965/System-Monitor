#include <string>

#include "format.h"

using std::string;

// INPUT: Long int measuring seconds
// OUTPUT: HH:MM:SS
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
