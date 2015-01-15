#ifndef TILESETCONTROLLER_HPP
#define TILESETCONTROLLER_HPP

#include <SFML/Graphics/RenderTexture.hpp>

#include <SFGUI/Canvas.hpp>
#include <SFGUI/Entry.hpp>
#include <SFGUI/Notebook.hpp>
#include <SFGUI/Scale.hpp>
#include <SFGUI/Scrollbar.hpp>
#include <SFGUI/Window.hpp>

namespace sfg
{
  class Desktop;
}

struct TilesetPage
{
  sfg::Canvas::Ptr canvas;
  sfg::Scrollbar::Ptr hScrollbar;
  sfg::Scrollbar::Ptr vScrollbar;
  std::string texName;
};

class TilesetManager;

class TilesetController
{
public:
  TilesetController(TilesetManager &tilesetManager, sfg::Desktop &desktop);

  void update();

  void redrawCanvas();
  void updateScrolbars();

private:

  void openLoadTilesetDialog();
  void loadNewTileset();

  void updateActiveCanvas();
  void updateZoom();
  void updateOffset();

  void addTilesetToView(const std::string &name);

  void initGui();
  void initTilesetWindow();
  void initLoadTilesetDialog();

private:
  TilesetManager &mTilesetManager;
  sfg::Desktop &mDesktop;

  sf::RenderTexture mRenderTex;
  float mCurrentZoom = 1.f;
  sf::Vector2f mCurrentOffset;

  struct
  {
    sfg::Notebook::Ptr notebook = nullptr;
    sfg::Window::Ptr loadTilesetDialog = nullptr;
    sfg::Entry::Ptr loadTilesetName = nullptr;
    std::vector<TilesetPage> tilesetPages;
    TilesetPage* activePage = nullptr;
    sfg::Scale::Ptr zoomScale = nullptr;
    sfg::Entry::Ptr zoomEntry = nullptr;
  } mGui;
};

#endif