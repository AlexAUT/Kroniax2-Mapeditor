#ifndef DRAWINGCONTROLLER_HPP
#define DRAWINGCONTROLLER_HPP

#include <SFML/Graphics/RectangleShape.hpp>

namespace sf
{
  class Event;
  class RenderWindow;
}

class SelectionManager;
class LayerManager;

class DrawingController
{
public:
  DrawingController(SelectionManager &selectionManager, LayerManager &layerManager);

  void handleEvent(const sf::Event &event);
  void render(sf::RenderWindow &window);
private:
  void updateHighlightRect(const sf::Event &event);
  void addTile(sf::Vector2i mousePos);

  sf::Vector2i getTileIndex(sf::Vector2i mousePos);
  sf::Vector2f getTilePosition(const sf::Event &event);

private:
  SelectionManager &mSelectionManager;
  LayerManager &mLayerManager;

  sf::RectangleShape mHighlightRect;

  bool mIsLeftPressed;
};

#endif