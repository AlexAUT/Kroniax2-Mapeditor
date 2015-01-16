#ifndef DRAWINGCONTROLLER_HPP
#define DRAWINGCONTROLLER_HPP

#include <SFML/Graphics/RectangleShape.hpp>

namespace sf
{
  class Event;
  class RenderWindow;
}

class SelectionManager;

class DrawingController
{
public:
  DrawingController(SelectionManager &selectionManager);

  void handleEvent(const sf::Event &event);
  void render(sf::RenderWindow &window);
private:
  void updateHighlightRect(const sf::Event &event);

private:
  SelectionManager &mSelectionManager;

  sf::RectangleShape mHighlightRect;
};

#endif