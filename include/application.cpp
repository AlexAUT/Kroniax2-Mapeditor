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

