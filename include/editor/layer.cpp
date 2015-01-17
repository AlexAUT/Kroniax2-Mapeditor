#include "layer.hpp"

#include <iostream>

Layer::Layer(sf::Vector2i tileSize, TilesetManager &tilesetManager):
  mTileSize(tileSize),
  mTilesetManager(tilesetManager)
{

}

void Layer::update()
{
  mRenderer.update();
}

void Layer::render(sf::RenderWindow &window)
{
  if (mVisible)
    mRenderer.render(window);
}

void Layer::addTile(sf::Vector2i index, std::size_t tex_ID, sf::Vector2i tile_index, std::size_t rotation)
{
  std::cout << "Added new tile: " << index.x << " | " << index.y << std::endl;
  int chunkIndex = checkIfOnChunk(index);
  if (checkIfOnChunk(index) < 0)
  {
    std::cout << "Added new junk" << std::endl;
    addNewChunk(index);
    chunkIndex = mChunks.size() - 1;
  }
  mChunks[chunkIndex]->addTile(index, tex_ID, tile_index, rotation);
}

sf::Vector2i Layer::getTileSize() const
{
  return mTileSize;
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

void Layer::addNewChunk(sf::Vector2i index)
{
  int startXIndex = index.x - (index.x % WIDTH);
  int startYIndex = index.y - (index.y % HEIGHT);
  sf::Vector2f startPos = {
    static_cast<float>(startXIndex * mTileSize.x),
    static_cast<float>(startYIndex * mTileSize.y)
  };
  mChunks.push_back(std::move(std::make_unique<TileChunk>(startPos, static_cast<sf::Vector2f>(mTileSize))));
  std::cout << "Added new junk at: " << startPos.x << " | " << startPos.y << std::endl;
  mRenderer.addChunkRenderer(*mChunks.back(), mTilesetManager);
}

int Layer::checkIfOnChunk(sf::Vector2i index) const
{
  for (int i = 0; i < static_cast<int>(mChunks.size()); i++)
  {
    if (mChunks[i]->contains(index))
      return i;
  }
  return -1;
}