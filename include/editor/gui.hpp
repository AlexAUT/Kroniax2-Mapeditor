#ifndef GUI_HPP
#define GUI_HPP

#include <SFML/Graphics/Image.hpp>

#include <SFGUI/SFGUI.hpp>
#include <SFGUI/Desktop.hpp>
#include <SFGUI/Entry.hpp>
#include <SFGUI/Notebook.hpp>
#include <SFGUI/Window.hpp>

namespace sf
{
  class Event;
  class RenderWindow;
}

class Application;

class Gui
{
public:
  Gui(Application &app);

  bool handleEvent(const sf::Event &event);
  void update(float seconds);

  void display();

  sfg::Desktop& getDesktop();
  const sfg::Desktop& getDesktop() const;

private:
  void loadTileset();

  void initGui();
  void initMenuBar();
  void initLayerWindow();
  void initSelectionWindow();
  
private:
  Application &mApplication;

  sfg::SFGUI mGui;
  sfg::Desktop mDesktop;

  sf::Image sfImg;

  sfg::Notebook::Ptr mTilesetNotebook;
  struct
  {
    sfg::Window::Ptr window;
    sfg::Entry::Ptr tilesetName;
  }mLoadTilesetDialog;
};

#endif