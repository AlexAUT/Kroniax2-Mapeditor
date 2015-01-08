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

#include "application.hpp"

#include "aw/utilities/log.hpp"

#include <exception>

Application::Application()
{
  initMainWindow();
  initGui();
}

int Application::run()
{
  while (mMainWindow.isOpen())
  {
    sf::Event event;
    while (mMainWindow.pollEvent(event))
    {
      if (event.type == sf::Event::Closed)
        mMainWindow.close();
    }

    mMainWindow.clear();
    mMainWindow.display();
  }

  return 0;
}

void Application::initMainWindow()
{
  mMainWindow.create({ 1200, 750 }, "Kroniax2-Mapeditor");
  mMainWindow.setVerticalSyncEnabled(true);
}

void Application::initGui()
{
  mGui.setWindow(mMainWindow);
  mGui.setGlobalFont("data/fonts/DejaVu.ttf");
}

