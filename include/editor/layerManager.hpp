#ifndef LAYERMANAGER_HPP
#define LAYERMANAGER_HPP

#include "layer.hpp"

#include <string>
#include <map>

#include <SFML/System/Vector2.hpp>

class LayerManager
{
public:

  bool addLayer(const std::string &name, sf::Vector2i tileSize);

  Layer& getLayer(const std::string &name);
  const Layer& getLayer(const std::string &name) const;



private:

private:
  std::map<std::string, Layer> mLayers;
};

#endif