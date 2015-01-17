#include "drawingController.hpp"

#include "selectionManager.hpp" 
#include "layerManager.hpp"

#include "utility/mouseOnWindowChecker.hpp"

#include <iostream>

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>


DrawingController::DrawingController(sf::RenderWindow &window, SelectionManager &selectionManager, LayerManager &layerManager) :
  mWindow(window),
  mSelectionManager(selectionManager),
  mLayerManager(layerManager),
  mIsLeftPressed(false),
  mView({ 600, 375 }, {1200, 750})
{

}

void DrawingController::handleEvent(const sf::Event &event)
{
  //Check if the mouse is on "free" space
  if (!MouseOnWindowChecker::getInstance().isMouseOnWidget())
  {
    if (event.type == sf::Event::MouseMoved)
    {
      if (mIsLeftPressed)
        addTile({ event.mouseMove.x, event.mouseMove.y });
      else if (mIsRightPressed)
        moveView({ event.mouseMove.x, event.mouseMove.y });
      else
        updateHighlightRect(event);
    }
    else if (event.type == sf::Event::MouseWheelMoved)
      zoomView(event.mouseWheel.delta);
    else if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
    {
      addTile({ event.mouseButton.x, event.mouseButton.y });
      mIsLeftPressed = true;
    }
    else if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left)
      mIsLeftPressed = false;
    else if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Right)
    {
      mLastMousePos = { event.mouseButton.x, event.mouseButton.y };
      mIsRightPressed = true;
    }
    else if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Right)
      mIsRightPressed = false;
  }
}

void DrawingController::render(sf::RenderWindow &window)
{
  window.setView(mView);
  mLayerManager.render(window);
  if (!mIsLeftPressed && !mIsRightPressed)
    window.draw(mHighlightRect);
}

void DrawingController::moveView(sf::Vector2i mousePos)
{
  auto offset = mWindow.mapPixelToCoords(mousePos, mView) - mWindow.mapPixelToCoords(mLastMousePos, mView);
  mLastMousePos = mousePos;
  mView.move(-offset);
}

void DrawingController::zoomView(int delta)
{
  mView.zoom(1.f + (0.05f * delta));
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
  auto mouseOnView = mWindow.mapPixelToCoords(mousePos, mView);
  sf::Vector2i index = {
    static_cast<int>(mouseOnView.x) / selection.tileSize.x,
    static_cast<int>(mouseOnView.y) / selection.tileSize.y
  };
  return index;
}

sf::Vector2f DrawingController::getTilePosition(const sf::Event &event)
{
  auto &selection = mSelectionManager.getSelection();
  auto mousePos = mWindow.mapPixelToCoords({ event.mouseMove.x, event.mouseMove.y }, mView);
  sf::Vector2f pos = {
    static_cast<float>(static_cast<int>(mousePos.x / selection.tileSize.x) * selection.tileSize.x),
    static_cast<float>(static_cast<int>(mousePos.y / selection.tileSize.y) * selection.tileSize.y)
  };

  return pos;
}