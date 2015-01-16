#ifndef SELECTION_MANAGER_HPP
#define SELECTION_MANAGER_HPP

#include <cstddef>

#include <SFML/System/Vector2.hpp>

namespace sf
{
  class Texture;
}

class TilesetManager;

struct Selection
{
  const sf::Texture *tex;
  int texIndex;
  sf::Vector2i selectedTile;
  sf::Vector2i tileSize;
  short rotation;
};

class SelectionManager
{
public:
  SelectionManager(TilesetManager &tilesetManager);

  void setTexture(const sf::Texture *tex);
  void setTextureIndex(int index);
  void setRotation(short rotation);
  void setSelectedTile(sf::Vector2i tileIndex);
  void setTileSize(sf::Vector2i tileSize);

  const Selection& getSelection() const;

private:

private:
  TilesetManager &mTilesetManager;

  Selection mSelection;
  
};

#endif