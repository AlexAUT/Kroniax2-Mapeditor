#ifndef GUI_HPP
#define GUI_HPP

#include <SFML/Graphics/Image.hpp>

#include <SFGUI/SFGUI.hpp>
#include <SFGUI/Desktop.hpp>

namespace sf
{
  class Event;
  class RenderWindow;
}

class Application;

class Gui
{
public:
  Gui(Application &app, bool &usedEvent);

  bool handleEvent(const sf::Event &event);
  void update(float seconds);

  void display();

  sfg::Desktop& getDesktop();
  const sfg::Desktop& getDesktop() const;

private:

  void initGui();
  void initMenuBar();
  
private:
  Application &mApplication;
  bool &mUsedEvent;

  sfg::SFGUI mGui;
  sfg::Desktop mDesktop;
};

#endif