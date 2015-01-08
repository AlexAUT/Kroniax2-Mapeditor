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