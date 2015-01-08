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
}