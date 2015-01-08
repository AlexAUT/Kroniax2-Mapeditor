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


#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include <SFML/Graphics/RenderWindow.hpp>

#include <TGUI/Gui.hpp>

class Application
{
public:
  Application();

  int run();

private:

  void initMainWindow();
  void initGui();

private:
  sf::RenderWindow mMainWindow;
  tgui::Gui mGui;
};

#endif
