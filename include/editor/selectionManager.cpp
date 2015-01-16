#include "selectionManager.hpp"

#include <iostream>

SelectionManager::SelectionManager(TilesetManager &tilesetManager) :
  mTilesetManager(tilesetManager),
  mSelection({ nullptr, -1, { -1, -1 }, { -1, -1 }, 0, })
{
  
}

void SelectionManager::setTexture(const sf::Texture *tex)
{
  mSelection.tex = tex;
}

void SelectionManager::setTextureIndex(int index)
{
  std::cout << "Change selected texture to " << index << std::endl;
  mSelection.texIndex = index;
}

void SelectionManager::setRotation(short rotation)
{
  std::cout << "Changed rotation to " << rotation << std::endl;
  mSelection.rotation = rotation;
}

void SelectionManager::setSelectedTile(sf::Vector2i tileIndex)
{
  mSelection.selectedTile = tileIndex;
}

void SelectionManager::setTileSize(sf::Vector2i tileSize)
{
  mSelection.tileSize = tileSize;
}

const Selection& SelectionManager::getSelection() const
{
  return mSelection;
}