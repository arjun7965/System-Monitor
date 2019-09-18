#ifndef FORMAT_H
#define FORMAT_H

#include <string>

namespace Format {
  std::string ElapsedTime(long time);  // converts time in seconds to 'HH:MM:SS up * day' format
  std::string Time(long time);         // converts time on seconds to 'HH:MM:SS' format
};

#endif
