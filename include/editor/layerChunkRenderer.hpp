#ifndef LAYERCHUNKRENDERER_HPP
#define LAYERCHUNKRENDERER_HPP

#include <vector>

#include <SFML/Graphics/VertexArray.hpp>

class TileChunk;
class TilesetManager;

namespace sf
{
  class RenderWindow;
}

class LayerChunkRenderer
{
public:
  LayerChunkRenderer(TileChunk &chunk, TilesetManager &tilesetManager);

  void update();
  void render(sf::RenderWindow &window);

private:

  void addRect(sf::Vector2f pos, int textureIndex, sf::Vector2i tileOfTexture, unsigned rotation);

private:
  TileChunk &mChunk;
  TilesetManager &mTilesetManager;

  std::vector<sf::VertexArray> mVertexArrays;
};

#endif