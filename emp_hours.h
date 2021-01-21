#ifndef EMP_HOURS_H
#define EMP_HOURS_H

#include <string>

struct employee {
  int id;
  std::string password;
  std::string first_name;
  std::string last_name;
};

struct Hours {
  std::string day;
  std::string open_hour;
  std::string close_hour;
};

// std::ostream& operator << (std::ostream& o, const Hours& h);
#endif