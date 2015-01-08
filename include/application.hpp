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
