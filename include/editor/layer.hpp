#ifndef LAYER_HPP
#define LAYER_HPP

#include "layerRenderer.hpp"
#include "tileChunk.hpp"

#include <vector>
#include <memory>

#include <SFML/System/Vector2.hpp>

class Layer
{
public:
  Layer(sf::Vector2i tileSize, TilesetManager &tilesetManager);

  void update();
  void render(sf::RenderWindow &window);

  void addTile(sf::Vector2i index, std::size_t tex_ID, sf::Vector2i tile_index, std::size_t rotation);

  sf::Vector2i getTileSize() const;

  void toggleVisible();
  bool getVisible() const;

  void toggleLocked();
  bool getLocked() const;

private:
  void addNewChunk(sf::Vector2i index);
  int checkIfOnChunk(sf::Vector2i index) const;

private:
  sf::Vector2i mTileSize;
  TilesetManager &mTilesetManager;

  bool mVisible = true;
  bool mLocked = false;

  LayerRenderer mRenderer;
  std::vector<std::shared_ptr<TileChunk> > mChunks;  
};

#endif