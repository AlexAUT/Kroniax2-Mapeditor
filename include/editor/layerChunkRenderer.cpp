#include "layerChunkRenderer.hpp"

#include "tileChunk.hpp"
#include "tilesetManager.hpp"

#include <iostream>

#include <SFML/Graphics/RenderWindow.hpp>

LayerChunkRenderer::LayerChunkRenderer(TileChunk &chunk, TilesetManager &tilesetManager) :
  mChunk(chunk),
  mTilesetManager(tilesetManager)
{
  std::cout << "Created junk renderer" << std::endl;
}

void LayerChunkRenderer::update()
{
  if (mChunk.hasChanged())
  {
    mVertexArrays.clear();
    for (unsigned i = 0; i < mTilesetManager.getTilesetCount(); i++)
      mVertexArrays.emplace_back(sf::Triangles, 0);

    for (int i = 0; i < WIDTH; i++)
    {
      for (int j = 0; j < HEIGHT; j++)
      {
        sf::Vector2f pos(mChunk.getPosition().x + (mChunk.getTileSize().x * i),
          mChunk.getPosition().y + (mChunk.getTileSize().y * j));
        auto tileIndex = (j * WIDTH) + i;
        addRect(pos, mChunk.getTile(tileIndex).tex_ID, mChunk.getTile(tileIndex).tile_index, mChunk.getTile(tileIndex).rotation);
      }
    }
  }
}

void LayerChunkRenderer::render(sf::RenderWindow &window)
{
  for (unsigned i = 0; i < mVertexArrays.size(); i++)
  {
    sf::RenderStates states;
    states.texture = &mTilesetManager.getTileset(i);
    window.draw(mVertexArrays[i], states);
  }
}

void LayerChunkRenderer::addRect(sf::Vector2f pos, int textureIndex, sf::Vector2i tileOfTexture, unsigned rotation)
{
  if (textureIndex < 0)
    return;
  //Left upper
  auto tileSize = mChunk.getTileSize();
  float l = pos.x;
  float t = pos.y;
  float r = pos.x + tileSize.x;
  float b = pos.y + tileSize.y;
  float tl = tileOfTexture.x * tileSize.x;
  float tt = tileOfTexture.y * tileSize.y;
  float tr = (tileOfTexture.x + 1) * tileSize.x;
  float tb = (tileOfTexture.y + 1) * tileSize.y;
  
  if (rotation == 0)
  {
    mVertexArrays[textureIndex].append({ { l, t }, { tl, tt } });//Left top
    mVertexArrays[textureIndex].append({ { r, t }, { tr, tt } });//Right top
    mVertexArrays[textureIndex].append({ { l, b }, { tl, tb } });//Left bot
    mVertexArrays[textureIndex].append({ { l, b }, { tl, tb } });//Left bot
    mVertexArrays[textureIndex].append({ { r, b }, { tr, tb } });//Right bot
    mVertexArrays[textureIndex].append({ { r, t }, { tr, tt } });//Right top
  }
  else if (rotation == 90)
  {
    mVertexArrays[textureIndex].append({ { l, t }, { tl, tb } });//Left top
    mVertexArrays[textureIndex].append({ { r, t }, { tl, tt } });//Right top
    mVertexArrays[textureIndex].append({ { l, b }, { tr, tb } });//Left bot
    mVertexArrays[textureIndex].append({ { l, b }, { tr, tb } });//Left bot
    mVertexArrays[textureIndex].append({ { r, b }, { tr, tt } });//Right bot
    mVertexArrays[textureIndex].append({ { r, t }, { tl, tt } });//Right top
  }
  else if (rotation == 180)
  {
    mVertexArrays[textureIndex].append({ { l, t }, { tr, tb } });//Left top
    mVertexArrays[textureIndex].append({ { r, t }, { tl, tb } });//Right top
    mVertexArrays[textureIndex].append({ { l, b }, { tr, tt } });//Left bot
    mVertexArrays[textureIndex].append({ { l, b }, { tr, tt } });//Left bot
    mVertexArrays[textureIndex].append({ { r, b }, { tl, tt } });//Right bot
    mVertexArrays[textureIndex].append({ { r, t }, { tl, tb } });//Right top
  }
  else if (rotation == 270)
  {
    mVertexArrays[textureIndex].append({ { l, t }, { tr, tt } });//Left top
    mVertexArrays[textureIndex].append({ { r, t }, { tr, tb } });//Right top
    mVertexArrays[textureIndex].append({ { l, b }, { tl, tt } });//Left bot
    mVertexArrays[textureIndex].append({ { l, b }, { tl, tt } });//Left bot
    mVertexArrays[textureIndex].append({ { r, b }, { tl, tb } });//Right bot
    mVertexArrays[textureIndex].append({ { r, t }, { tr, tb } });//Right top
  }
}