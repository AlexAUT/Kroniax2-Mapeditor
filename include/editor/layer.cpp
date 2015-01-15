#include "layer.hpp"

Layer::Layer(sf::Vector2i tileSize):
  mTileSize(tileSize)
{

}

void Layer::toggleVisible()
{
  mVisible = !mVisible;
}

bool Layer::getVisible() const
{
  return mVisible;
}

void Layer::toggleLocked()
{
  mLocked = !mLocked;
}

bool Layer::getLocked() const
{
  return mLocked;
}
