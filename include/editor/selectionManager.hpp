#ifndef SELECTION_MANAGER_HPP
#define SELECTION_MANAGER_HPP

#include <cstddef>

namespace sf
{
  class Texture;
}

class TilesetManager;

struct Selection
{
  std::size_t texIndex;
  short rotation;
};

class SelectionManager
{
public:
  SelectionManager(TilesetManager &tilesetManager);

  void setTexture(std::size_t index);
  void setRotation(short rotation);

  const Selection& getSelection() const;

private:

private:
  TilesetManager &mTilesetManager;

  Selection mSelection;
  
};

#endif