#ifndef AW_LOG_HPP
#define AW_LOG_HPP

#include <string>
#include <fstream>

namespace aw
{
  class Log
  {
  public:
    ~Log();

    static Log& getInstance();

    //Specify the outputfile for the log.
    void setFilePath(const std::string &filePath);

    //This function will write "message" to stdout and
    //the file specified by setFilePath.
    template<class T>
    void write(const T &message);

  private:
    Log();
  
  private:
    std::fstream mLogFile;
  };
}

#include "log.inl"

#endif