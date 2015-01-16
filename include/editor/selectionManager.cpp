#include "selectionManager.hpp"

#include <iostream>

SelectionManager::SelectionManager(TilesetManager &tilesetManager) :
  mTilesetManager(tilesetManager),
  mSelection({-1, 0})
{
  
}

void SelectionManager::setTexture(std::size_t index)
{
  std::cout << "Change selected texture to " << index << std::endl;
  mSelection.texIndex = index;
}

void SelectionManager::setRotation(short rotation)
{
  std::cout << "Changed rotation to " << rotation << std::endl;
  mSelection.rotation = rotation;
}

const Selection& SelectionManager::getSelection() const
{
  return mSelection;
}