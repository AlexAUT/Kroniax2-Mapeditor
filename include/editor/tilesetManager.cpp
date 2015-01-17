#include "tilesetManager.hpp"

#include <cassert>

#include <SFML/Graphics/Sprite.hpp>

bool TilesetManager::loadTileset(const std::string &name)
{
  auto found = getTilesetIndex(name);
  if (found == -1)
  {
    mTilesets.push_back({ name, sf::Texture() });
    if (!mTilesets.back().second.loadFromFile("data/tilesets/" + name))
    {
      std::cout << "Failed" << std::endl;
      mTilesets.pop_back();
      return false;
    }
  }
  return true;
}

void TilesetManager::removeTileset(const std::string &name)
{
  auto found = getTilesetIndex(name);
  if (found != -1)
  {
    mTilesets.erase(mTilesets.begin() + found);
  }
}

const sf::Texture& TilesetManager::getTileset(unsigned index) const
{
  return mTilesets[index].second;
}

int TilesetManager::getTilesetIndex(const std::string &name) const
{
  for (int i = 0; i < static_cast<int>(mTilesets.size()); i++)
  {
    if (mTilesets[i].first == name)
      return i;
  }
  return -1;
}

const sf::Texture& TilesetManager::getTileset(const std::string &name) const
{
  auto index = getTilesetIndex(name);
  assert(index != -1);
  return mTilesets[index].second;
}

std::size_t TilesetManager::getTilesetCount() const
{
  return mTilesets.size();
}

void TilesetManager::drawTextureOnCanvas(sfg::Canvas::Ptr canvas, const std::string &name)
{
  std::cout << "Draw" << std::endl;
 // canvas->SetRequisition(static_cast<sf::Vector2f>(getTileset(name).getSize()));
  canvas->Create();
  sf::Sprite sprite(getTileset(name));
  canvas->Clear();
  canvas->Draw(sprite);
  canvas->Display();
}

void TilesetManager::mouseMoveOnTileset(sf::Event &event, sfg::Canvas::Ptr canvas, const std::string &name)
{

}

void TilesetManager::clickedOnTileset(sf::Event &event, sfg::Canvas::Ptr canvas, const std::string &name)
{

}