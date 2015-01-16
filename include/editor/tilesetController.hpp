#ifndef TILESETCONTROLLER_HPP
#define TILESETCONTROLLER_HPP

#include <memory>

#include <SFML/Graphics/RenderTexture.hpp>

namespace sfg
{
  class Desktop;
  class Canvas;
  class Entry;
  class Notebook;
  class Scale;
  class Scrollbar;
  class Window;
}

struct TilesetPage
{
  std::shared_ptr<sfg::Canvas> canvas;
  std::shared_ptr<sfg::Scrollbar> hScrollbar;
  std::shared_ptr<sfg::Scrollbar> vScrollbar;
  std::string texName;
};

class TilesetManager;
class SelectionManager;

class TilesetController
{
public:
  TilesetController(TilesetManager &tilesetManager, SelectionManager &selectionManager,
    sfg::Desktop &desktop);

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
  SelectionManager &mSelectionManager;
  sfg::Desktop &mDesktop;

  sf::RenderTexture mRenderTex;
  float mCurrentZoom = 1.f;
  sf::Vector2f mCurrentOffset;

  struct
  {
    std::shared_ptr<sfg::Notebook> notebook = nullptr;
    std::shared_ptr<sfg::Window> loadTilesetDialog = nullptr;
    std::shared_ptr<sfg::Entry> loadTilesetName = nullptr;
    std::vector<TilesetPage> tilesetPages;
    TilesetPage* activePage = nullptr;
    std::shared_ptr<sfg::Scale> zoomScale = nullptr;
    std::shared_ptr<sfg::Entry> zoomEntry = nullptr;
  } mGui;
};

#endif