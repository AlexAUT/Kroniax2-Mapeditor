#include "tileChunk.hpp"

#include <iostream>

#include <SFML/Graphics/Rect.hpp>

TileChunk::TileChunk()
{}

TileChunk::TileChunk(sf::Vector2f pos, sf::Vector2f tileSize) :
mPosition(pos), mTileSize(tileSize), mTiles(100*100)
{
  mOffsetIndex.x = static_cast<int>(pos.x / mTileSize.x);
  mOffsetIndex.y = static_cast<int>(pos.y / mTileSize.y);
}

void TileChunk::addTile(sf::Vector2i index, std::size_t tex_ID, sf::Vector2i tile_index, std::size_t rotation)
{
  auto &tile = getTile(index);
  tile.tex_ID = tex_ID;
  tile.tile_index = tile_index;
  tile.rotation = rotation;
  mChanged = true;
}

bool TileChunk::contains(sf::Vector2f pos) const
{
  sf::FloatRect bounds = { mPosition, mTileSize };
  bounds.width *= WIDTH;
  bounds.height *= HEIGHT;
  return bounds.contains(pos);
}

bool TileChunk::contains(sf::Vector2i index) const
{
  sf::Vector2f pos{ index.x * mTileSize.x, index.y * mTileSize.y };
  return contains(pos);
}

sf::Vector2f TileChunk::getPosition() const
{
  return mPosition;
}

sf::Vector2f TileChunk::getTileSize() const
{
  return mTileSize;
}

Tile& TileChunk::getTile(int index)
{
  return mTiles[index];
}

Tile& TileChunk::getTile(sf::Vector2i index)
{
  return mTiles[convertIndexToVectorIndex(index)];
}

bool TileChunk::hasChanged()
{
  bool val = mChanged;
  mChanged = false;
  return val;
}

std::size_t TileChunk::convertIndexToVectorIndex(sf::Vector2i index)
{
  sf::Vector2i relativToChunk = index - mOffsetIndex;
  return static_cast<unsigned>((relativToChunk.y * WIDTH) + relativToChunk.x);
}