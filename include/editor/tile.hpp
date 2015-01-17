#ifndef TILE_HPP
#define TILE_HPP

#include <cstddef> //std::size_t

#include <SFML/System/Vector2.hpp>

struct Tile
{
  std::size_t tex_ID = -1;
  sf::Vector2i tile_index;
  unsigned rotation;
  std::size_t color_ID;
};

#endif