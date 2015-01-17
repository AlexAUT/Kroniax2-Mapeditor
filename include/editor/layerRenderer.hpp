#ifndef LAYERRENDERER_HPP
#define LAYERRENDERER_HPP

#include "layerChunkRenderer.hpp"

#include <vector>

class TileChunk;

namespace sf
{
  class RenderWindow;
}

class LayerRenderer
{
public:

  void addChunkRenderer(TileChunk &chunk, TilesetManager &tilesetManager);

  void update();
  void render(sf::RenderWindow &window);

private:

private:
  std::vector<LayerChunkRenderer> mChunkRenderers;
};

#endif