#include "drawingController.hpp"

#include "selectionManager.hpp" 

#include <iostream>

#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/RenderWindow.hpp>


DrawingController::DrawingController(SelectionManager &selectionManager) :
  mSelectionManager(selectionManager)
{

}

void DrawingController::handleEvent(const sf::Event &event)
{
  if (event.type == sf::Event::MouseMoved)
    updateHighlightRect(event);
}

void DrawingController::render(sf::RenderWindow &window)
{
  window.draw(mHighlightRect);
}

void DrawingController::updateHighlightRect(const sf::Event &event)
{
  auto &selection = mSelectionManager.getSelection();
  if (selection.tex != nullptr && selection.tileSize.x >= 0 && selection.tileSize.y >= 0)
  {
    sf::Vector2i pos = {
      (event.mouseMove.x / selection.tileSize.x) * selection.tileSize.x,
      (event.mouseMove.y / selection.tileSize.y) * selection.tileSize.y
    };
    mHighlightRect.setPosition(static_cast<sf::Vector2f>(pos));
    mHighlightRect.setSize(static_cast<sf::Vector2f>(selection.tileSize));
    mHighlightRect.setFillColor({ 200, 200, 100, 125 });
  }
  else
  {
    mHighlightRect.setFillColor(sf::Color::Transparent);
  }
}