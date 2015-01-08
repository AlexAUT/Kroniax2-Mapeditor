#include <iostream>
#include <iomanip>
#include <ctime>

namespace aw
{
  template<class T>
  void Log::write(const T &message)
  {
    std::time_t t = std::time(nullptr);

    std::cout << message << std::endl;
    if (mLogFile.is_open())
      mLogFile << std::put_time(std::localtime(&t), "%c: ") << message << std::endl;
  }
}