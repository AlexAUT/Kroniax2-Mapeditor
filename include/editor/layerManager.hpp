#ifndef LAYERMANAGER_HPP
#define LAYERMANAGER_HPP

#include "layer.hpp"

#include <string>
#include <map>

#include <SFML/System/Vector2.hpp>

class LayerManager
{
public:

  void update();
  void render(sf::RenderWindow &window);

  bool addLayer(const std::string &name, sf::Vector2i tileSize, TilesetManager &tilesetManager);

  Layer& getLayer(const std::string &name);
  const Layer& getLayer(const std::string &name) const;

  void setActiveLayer(const std::string &name);
  std::string getActiveLayerName();
  Layer& getActiveLayer();
  const Layer& getActiveLayer() const;

private:

private:
  std::map<std::string, Layer> mLayers;

  std::string mActiveLayer;
};

#endif