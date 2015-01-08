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