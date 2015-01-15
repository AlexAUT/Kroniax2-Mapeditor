#include "tilesetManager.hpp"

#include <cassert>

#include <SFML/Graphics/Sprite.hpp>

bool TilesetManager::loadTileset(const std::string &name)
{
  auto found = mTilesets.find(name);
  if (found == mTilesets.end())
  {
    auto it = mTilesets.insert({ name, sf::Texture() });
    if (!it.first->second.loadFromFile("data/tilesets/" + name))
    {
      mTilesets.erase(it.first);
      return false;
    }
  }

  return true;
}

void TilesetManager::removeTileset(const std::string &name)
{
  auto found = mTilesets.find(name);
  if (found != mTilesets.end())
  {
    mTilesets.erase(found);
  }
}

const sf::Texture& TilesetManager::getTileset(const std::string &name) const
{
  auto found = mTilesets.find(name);
  assert(found != mTilesets.end());
  return found->second;
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