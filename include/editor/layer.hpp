#ifndef LAYER_HPP
#define LAYER_HPP

#include <SFML/System/Vector2.hpp>

class Layer
{
public:
  Layer(sf::Vector2i tileSize);

  sf::Vector2i getTileSize() const;

  void toggleVisible();
  bool getVisible() const;

  void toggleLocked();
  bool getLocked() const;

private:

private:
  sf::Vector2i mTileSize;

  bool mVisible = true;
  bool mLocked = false;
};

#endif