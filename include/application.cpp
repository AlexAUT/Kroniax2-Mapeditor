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

#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/Image.hpp>

#include <SFGUI/Button.hpp>
#include <SFGUI/Frame.hpp>
#include <SFGUI/Image.hpp>
#include <SFGUI/Scale.hpp>
#include <SFGUI/Window.hpp>
#include <SFGUI/Entry.hpp>
#include <SFGUI/RadioButton.hpp>
#include <SFGUI/Box.hpp>
#include <SFGUI/Label.hpp>
#include <SFGUI/Notebook.hpp>
#include <SFGUI/ToggleButton.hpp>

Application::Application() :
  mGui(*this),
  mTilesetController(mTilesetManager, mGui.getDesktop()),
  mLayerController(mLayerManager, mGui.getDesktop()),
  mSelectionManager(mTilesetManager),
  mSelectionController(mSelectionManager, mGui.getDesktop())
{
  initMainWindow();
}

int Application::run()
{
  while (mWindow.isOpen())
  {
    while (mWindow.pollEvent(mEvent))
    {
      if (!mGui.handleEvent(mEvent))
      {
        if (mEvent.type == sf::Event::Closed)
          mWindow.close();
      }
    }

    mGui.update(0.016f);
    mTilesetController.update();

    mWindow.clear(sf::Color(200, 200, 200));
    mGui.display();
    mWindow.display();
  }

  return 0;
}

void Application::initMainWindow()
{
  mWindow.create({ 1200, 750 }, "Kroniax2-Mapeditor");
  mWindow.setVerticalSyncEnabled(true);
}

