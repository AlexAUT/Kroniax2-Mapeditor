#include "drawingController.hpp"

#include "selectionManager.hpp" 
#include "layerManager.hpp"

#include <iostream>

#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/RenderWindow.hpp>


DrawingController::DrawingController(SelectionManager &selectionManager, LayerManager &layerManager) :
  mSelectionManager(selectionManager),
  mLayerManager(layerManager),
  mIsLeftPressed(false)
{

}

void DrawingController::handleEvent(const sf::Event &event)
{
  if (event.type == sf::Event::MouseMoved)
  {
    if (mIsLeftPressed)
      addTile({ event.mouseMove.x, event.mouseMove.y });
    else
      updateHighlightRect(event);
  }
  else if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
  {
    addTile({ event.mouseButton.x, event.mouseButton.y });
    mIsLeftPressed = true;
  }
  else if(event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left)
    mIsLeftPressed = false;
}

void DrawingController::render(sf::RenderWindow &window)
{
  window.draw(mHighlightRect);
}

void DrawingController::addTile(sf::Vector2i mousePos)
{
  auto selection = mSelectionManager.getSelection();

  if (mSelectionManager.getSelection().tileSize.x > 0)
    mLayerManager.getActiveLayer().addTile(getTileIndex(mousePos), selection.texIndex, selection.selectedTile, selection.rotation);
}

void DrawingController::updateHighlightRect(const sf::Event &event)
{
  auto &selection = mSelectionManager.getSelection();
  if (selection.tex != nullptr && selection.tileSize.x >= 0 && selection.tileSize.y >= 0)
  {
    mHighlightRect.setPosition(getTilePosition(event));
    mHighlightRect.setSize(static_cast<sf::Vector2f>(selection.tileSize));
    mHighlightRect.setFillColor({ 50, 200, 200, 125 });
  }
  else
  {
    mHighlightRect.setFillColor(sf::Color::Transparent);
  }
}

sf::Vector2i DrawingController::getTileIndex(sf::Vector2i mousePos)
{
  auto &selection = mSelectionManager.getSelection();
  sf::Vector2i index = {
    mousePos.x / selection.tileSize.x,
    mousePos.y / selection.tileSize.y
  };
  return index;
}

sf::Vector2f DrawingController::getTilePosition(const sf::Event &event)
{
  auto &selection = mSelectionManager.getSelection();
  sf::Vector2f pos = {
    static_cast<float>((event.mouseMove.x / selection.tileSize.x) * selection.tileSize.x),
    static_cast<float>((event.mouseMove.y / selection.tileSize.y) * selection.tileSize.y)
  };

  return pos;
}