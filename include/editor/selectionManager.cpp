#include "selectionManager.hpp"

SelectionManager::SelectionManager(TilesetManager &tilesetManager) :
  mTilesetManager(tilesetManager)
{

}


const Selection& SelectionManager::getSelection() const
{
  mSelection;
}