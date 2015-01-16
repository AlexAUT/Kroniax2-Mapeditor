#ifndef SELECTION_MANAGER_HPP
#define SELECTION_MANAGER_HPP

namespace sf
{
  class Texture;
}

class TilesetManager;

struct Selection
{
  sf::Texture *tex = nullptr;
};

class SelectionManager
{
public:
  SelectionManager(TilesetManager &tilesetManager);

  void setTexture();

  const Selection& getSelection() const;

private:

private:
  TilesetManager &mTilesetManager;

  Selection mSelection;
  
};

#endif