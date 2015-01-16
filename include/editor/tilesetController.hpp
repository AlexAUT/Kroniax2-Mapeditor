#ifndef TILESETCONTROLLER_HPP
#define TILESETCONTROLLER_HPP

#include <memory>

#include <SFML/Graphics/RenderTexture.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Sprite.hpp>

namespace sf
{
  class Window;
}

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
  TilesetController(sf::Window &window, TilesetManager &tilesetManager, SelectionManager &selectionManager,
    sfg::Desktop &desktop);

  void update();

  void redrawCanvas();
  void updateScrolbars();

private:

  void updateSelectedTile();
  void updateMouseOverTile();
  sf::Vector2i getTileMouseIsOver();

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
  sf::Window &mWindow;
  TilesetManager &mTilesetManager;
  SelectionManager &mSelectionManager;
  sfg::Desktop &mDesktop;

  sf::Vector2i mSelectedTile = { -1, -1 };
  sf::Vector2i mMouseOverTile = { -1, -1 };
  sf::Vector2i mTileSize = { 24, 24 };

  sf::RectangleShape mSelectionRect;
  sf::RectangleShape mMouseOverRect;

  sf::RenderTexture mRenderTex;
  sf::Sprite mRenderSprite;
  sf::View mView;
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