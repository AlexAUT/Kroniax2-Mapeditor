#include "layerManager.hpp"

#include <cassert>

void LayerManager::update()
{
  for (auto &it : mLayers)
    it.second.update();
}

void LayerManager::render(sf::RenderWindow &window)
{
  for (auto &it : mLayers)
    it.second.render(window);
}

bool LayerManager::addLayer(const std::string &name, sf::Vector2i tileSize, TilesetManager &tilesetManager)
{
  auto found = mLayers.find(name);
  if (found == mLayers.end())
  {
    auto it = mLayers.insert({ name, { tileSize, tilesetManager } });
    return true;
  }
  return false;
}

Layer& LayerManager::getLayer(const std::string &name)
{
  auto found = mLayers.find(name);
  assert(found != mLayers.end());
  return found->second;
}

const Layer& LayerManager::getLayer(const std::string &name) const
{
  auto found = mLayers.find(name);
  assert(found != mLayers.end());
  return found->second;
}

void LayerManager::setActiveLayer(const std::string &name)
{
  mActiveLayer = name;
}

std::string LayerManager::getActiveLayerName()
{
  return mActiveLayer;
}

Layer& LayerManager::getActiveLayer()
{
  return getLayer(mActiveLayer);
}

const Layer& LayerManager::getActiveLayer() const
{
  return getLayer(mActiveLayer);
}