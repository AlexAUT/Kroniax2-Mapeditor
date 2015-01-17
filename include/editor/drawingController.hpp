#ifndef DRAWINGCONTROLLER_HPP
#define DRAWINGCONTROLLER_HPP

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/View.hpp>

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
  DrawingController(sf::RenderWindow &window, SelectionManager &selectionManager, LayerManager &layerManager);

  void handleEvent(const sf::Event &event);
  void render(sf::RenderWindow &window);
private:
  void moveView(sf::Vector2i position);
  void zoomView(int delta);

  void updateHighlightRect(const sf::Event &event);
  void addTile(sf::Vector2i mousePos);

  sf::Vector2i getTileIndex(sf::Vector2i mousePos);
  sf::Vector2f getTilePosition(const sf::Event &event);

private:
  sf::RenderWindow &mWindow;
  SelectionManager &mSelectionManager;
  LayerManager &mLayerManager;

  sf::RectangleShape mHighlightRect;

  bool mIsLeftPressed;
  bool mIsRightPressed;

  sf::Vector2i mLastMousePos;

  sf::View mView;
};

#endif