#include "log.hpp"

namespace aw
{
  Log::Log()
  {

  }

  Log::~Log()
  {
    mLogFile.close();
  }

  Log& Log::getInstance()
  {
    std::cout << "Hier";
    static Log log;
    return log;
  }

  void Log::setFilePath(const std::string &filePath)
  {
    mLogFile.open(filePath.c_str(), std::ios::app);
  }

  template<class T>
  void Log::write(const T &message)
  {
    std::time_t t = std::time(nullptr);

    std::cout << message << std::endl;
    if (mLogFile.is_open())
      mLogFile << std::put_time(std::localtime(&t), "%c: ") << message << std::endl;
  }
}