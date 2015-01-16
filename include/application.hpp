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
#include <SFML/Window/Event.hpp>

#include "editor/gui.hpp"
#include "editor/tilesetManager.hpp"
#include "editor/tilesetController.hpp"
#include "editor/layerController.hpp"
#include "editor/layerManager.hpp"
#include "editor/selectionController.hpp"
#include "editor/selectionManager.hpp"

class Application
{
public:
  //Allow the Gui class to access the member.
  friend class Gui;

  Application();

  int run();

private:

  void initMainWindow();

private:

  sf::RenderWindow mWindow;
  sf::Event mEvent;
  Gui mGui;
  TilesetManager mTilesetManager;
  TilesetController mTilesetController;
  LayerManager mLayerManager;
  LayerController mLayerController;
  SelectionManager mSelectionManager;
  SelectionController mSelectionController;

  bool mGuiUsedEvent;
};

#endif
