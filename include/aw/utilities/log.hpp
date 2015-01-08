////////////////////////////////////////////////////////////
//
// Kroniax2-Mapeditor
// Copyright (C) 2015 Alexander Weinrauch (alexander.weinrauch@gmail.com)
//
// This software is provided 'as-is', without any express or implied warranty.
// In no event will the authors be held liable for any damages arising from the use of this software.
//
// License information at https://github.com/AlexAUT/Kroniax2-Mapeditor/blob/master/LICENSE
//
////////////////////////////////////////////////////////////


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