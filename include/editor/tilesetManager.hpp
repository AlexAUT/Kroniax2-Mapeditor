#ifndef TILESET_MANAGER_HPP
#define TILESET_MANAGER_HPP

#include <vector>
#include <utility>

#include <SFML/Graphics/Texture.hpp>

#include <SFGUI/Canvas.hpp>

class TilesetManager
{
public:
  bool loadTileset(const std::string &name);
  void removeTileset(const std::string &name);

  int getTilesetIndex(const std::string &name) const;
  const sf::Texture& getTileset(const std::string &name) const;

  std::size_t getTilesetCount() const;

  //Callbacks for gui
  void drawTextureOnCanvas(sfg::Canvas::Ptr canvas, const std::string &name);
  void mouseMoveOnTileset(sf::Event &event, sfg::Canvas::Ptr canvas, const std::string &name);
  void clickedOnTileset(sf::Event &event, sfg::Canvas::Ptr canvas, const std::string &name);

private:

private:
  std::vector<std::pair<std::string, sf::Texture>> mTilesets;
};

#endif