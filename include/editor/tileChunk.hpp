#ifndef TILECHUNK_HPP
#define TILECHUNK_HPP

#include "tile.hpp"

#include <vector>

#include <SFML/System/Vector2.hpp>

static const unsigned WIDTH = 10;
static const unsigned HEIGHT = 10;

class TileChunk
{
public:
  TileChunk();
  TileChunk(sf::Vector2f pos, sf::Vector2f tileSize);

  void addTile(sf::Vector2i index, std::size_t tex_ID, sf::Vector2i tile_index, std::size_t rotation);

  bool contains(sf::Vector2f pos) const;
  bool contains(sf::Vector2i index) const;

  bool hasChanged();

  sf::Vector2f getPosition() const;
  sf::Vector2f getTileSize() const;

  Tile& getTile(int index);
  Tile& getTile(sf::Vector2i);
  std::size_t convertIndexToVectorIndex(sf::Vector2i index);
private:
  

private:
  sf::Vector2f mPosition;
  sf::Vector2i mOffsetIndex;
  sf::Vector2f mTileSize;

  std::vector<Tile> mTiles;

  bool mChanged; //Used to say the Renderer to update his visuals
};

#endif