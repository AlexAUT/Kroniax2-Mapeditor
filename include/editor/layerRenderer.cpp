#include "layerRenderer.hpp"

void LayerRenderer::addChunkRenderer(TileChunk &chunk, TilesetManager &tilesetManager)
{
  mChunkRenderers.push_back({ chunk, tilesetManager });
}

void LayerRenderer::update()
{
  for (auto &it : mChunkRenderers)
    it.update();
}

void LayerRenderer::render(sf::RenderWindow &window)
{
  for (auto &it : mChunkRenderers)
    it.render(window);
}