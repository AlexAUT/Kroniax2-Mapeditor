#include "tilesetController.hpp"

#include "tilesetManager.hpp"
#include "selectionManager.hpp"

#include <SFML/Graphics/Image.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

#include <SFGUI/Adjustment.hpp>
#include <SFGUI/Box.hpp>
#include <SFGUI/Button.hpp>
#include <SFGUI/Canvas.hpp>
#include <SFGUI/Desktop.hpp>
#include <SFGUI/Entry.hpp>
#include <SFGUI/Frame.hpp>
#include <SFGUI/Image.hpp>
#include <SFGUI/Label.hpp>
#include <SFGUI/Notebook.hpp>
#include <SFGUI/Scale.hpp>
#include <SFGUI/Scrollbar.hpp>
#include <SFGUI/Window.hpp>

TilesetController::TilesetController(sf::Window &window, TilesetManager &tilesetManager, SelectionManager &selectionManager,
              sfg::Desktop &desktop, bool &usedEvent) :
  mWindow(window),
  mTilesetManager(tilesetManager),
  mSelectionManager(selectionManager),
  mDesktop(desktop),
  mUsedEvent(usedEvent)
{
  initGui();
}

void TilesetController::update()
{
  //Offset
  static auto lastOffset = mCurrentOffset;
  if (lastOffset != mCurrentOffset)
  {
    lastOffset = mCurrentOffset;
  }
  //Zoom
  static auto lastZoom = mCurrentZoom;
  mCurrentZoom = mGui.zoomScale->GetValue();
  if (lastZoom != mCurrentZoom)
  {
    auto cursorPos = mGui.zoomEntry->GetCursorPosition();
    mGui.zoomEntry->SetText(std::to_string(static_cast<int>(mCurrentZoom * 100)) + "%");
    mGui.zoomEntry->SetCursorPosition(cursorPos);
    lastZoom = mCurrentZoom;
  }
  //Size
  static auto lastSize = mGui.notebook->GetAllocation();
  auto currentSize = mGui.notebook->GetAllocation();
  if (lastSize.width != currentSize.width || lastSize.height != currentSize.height)
  {
    lastSize = currentSize;
  }

  updateMouseOverTile();
  redrawCanvas();
}

void TilesetController::redrawCanvas()
{
  if (mGui.tilesetPages.size() != 0)
  {
    std::cout << "Redraw, canvas: " << mGui.activePage->texName << std::endl;
    auto &tex = mTilesetManager.getTileset(mGui.activePage->canvas->GetId());
    if (mRenderTex.getSize() != sf::Vector2u(static_cast<unsigned>(mGui.activePage->canvas->GetAllocation().width), 
      static_cast<unsigned>(mGui.activePage->canvas->GetAllocation().height)))
    {
      std::cout << "Recreated texture" << std::endl;
      mRenderTex.create(static_cast<unsigned>(mGui.activePage->canvas->GetAllocation().width),
        static_cast<unsigned>(mGui.activePage->canvas->GetAllocation().height));
    }

    mRenderSprite = sf::Sprite(tex);
    mRenderSprite.scale({ mCurrentZoom, mCurrentZoom });
    mView = mRenderTex.getDefaultView();
    mView.setCenter({ mCurrentOffset.x + mRenderSprite.getGlobalBounds().width / 2.f, mCurrentOffset.y + mRenderSprite.getGlobalBounds().height / 2.f });
    mRenderTex.setView(mView);
    mRenderTex.clear();
    mRenderTex.draw(mRenderSprite);
    mRenderTex.draw(mMouseOverRect);
    mRenderTex.draw(mSelectionRect);
    mRenderTex.display();
    sf::Sprite sprite2(mRenderTex.getTexture());
    std::cout << "Draw" << std::endl;
    mGui.activePage->canvas->Clear();
    mGui.activePage->canvas->Draw(sprite2);
    std::cout << "Offset: " << mCurrentOffset.x << " | " << mCurrentOffset.y << std::endl;
    auto difference_x = mRenderSprite.getGlobalBounds().width - mRenderTex.getSize().x;
    if (difference_x > 0)
    {
      mGui.activePage->hScrollbar->Show(true);
      auto adj = mGui.activePage->hScrollbar->GetAdjustment();
      adj->Configure(mCurrentOffset.x, -difference_x / 2.f, difference_x / 2.f, difference_x / 100.f, difference_x / 5.f, 1);
    }
    else
    {
      mGui.activePage->hScrollbar->SetValue(0);
      mGui.activePage->hScrollbar->GetAdjustment()->Configure(0, 0, 0, 0, 0, 1);
    }
    auto difference_y = mRenderSprite.getGlobalBounds().height - mRenderTex.getSize().y;
    if (difference_y > 0)
    {
      mGui.activePage->vScrollbar->Show(true);
      auto adj = mGui.activePage->vScrollbar->GetAdjustment();
      adj->Configure(mCurrentOffset.y, -difference_y / 2.f, difference_y / 2.f, difference_y / 100.f, difference_y / 5.f, 1.f);
    }
    else
    {
      mGui.activePage->vScrollbar->SetValue(0);
      mGui.activePage->vScrollbar->GetAdjustment()->Configure(0, 0, 0, 0, 0, 1);
    }
  }
}

void TilesetController::updateSelectedTile()
{
  auto tileSize = mSelectionManager.getSelection().tileSize;
  auto tile = getTileMouseIsOver();
  auto currentTex = mTilesetManager.getTileset(mGui.activePage->texName);
  if (tileSize.x > 0 && tileSize.y > 0)
  {
    if (tile.x >= 0 && (tile.x + 1) * tileSize.x <= static_cast<int>(currentTex.getSize().x) &&
      tile.y >= 0 && (tile.y + 1) * tileSize.y <= static_cast<int>(currentTex.getSize().y))
    {
      mSelectedTile = tile;
      mSelectionManager.setSelectedTile(mSelectedTile);
      std::cout << "Selected tile: " << mSelectedTile.x << " | " << mSelectedTile.y << std::endl;
      mSelectionRect.setSize(static_cast<sf::Vector2f>(tileSize));
      mSelectionRect.setScale(mRenderSprite.getScale());
      sf::Vector2f pos = {
        static_cast<float>(mSelectedTile.x * tileSize.x) * mRenderSprite.getScale().x,
        static_cast<float>(mSelectedTile.y * tileSize.y) * mRenderSprite.getScale().y
      };
      mSelectionRect.setPosition(pos);
      mSelectionRect.setFillColor(sf::Color(0, 200, 12, 125));
    }
  }
}

void TilesetController::updateMouseOverTile()
{
  auto tileSize = mSelectionManager.getSelection().tileSize;
  if (tileSize.x > 0 && tileSize.y > 0 && mTilesetManager.getTilesetCount() > 0)
  {
    auto tile = getTileMouseIsOver();
    auto currentTex = mTilesetManager.getTileset(mGui.activePage->texName);
    if (tile.x < 0 || (tile.x + 1) * tileSize.x > static_cast<int>(currentTex.getSize().x) ||
      tile.y < 0 || (tile.y + 1) * (tileSize.y) > static_cast<int>(currentTex.getSize().y))
    {
      //Hide mouseOver because we are not on the image
      mMouseOverRect.setSize({ 0.f, 0.f });
    }
    else
    {
      mMouseOverTile = tile;

      mMouseOverRect.setSize(static_cast<sf::Vector2f>(tileSize));
      mMouseOverRect.setScale(mRenderSprite.getScale());
      sf::Vector2f pos = {
        static_cast<float>(mMouseOverTile.x * tileSize.x) * mRenderSprite.getScale().x,
        static_cast<float>(mMouseOverTile.y * tileSize.y) * mRenderSprite.getScale().y
      };
      mMouseOverRect.setPosition(pos);
      mMouseOverRect.setFillColor(sf::Color(200, 12, 0, 125));

    redrawCanvas();
    }
  }
}

sf::Vector2i TilesetController::getTileMouseIsOver()
{
  sf::Vector2f mousePos = static_cast<sf::Vector2f>(sf::Mouse::getPosition(mWindow));
  mousePos = mousePos - (mGui.activePage->canvas->GetAbsolutePosition());
  std::cout << "MosuePos on Canvas: " << mousePos.x << " | " << mousePos.y << std::endl;
  sf::Vector2f difference = {
    mRenderSprite.getGlobalBounds().width - mRenderTex.getSize().x,
    mRenderSprite.getGlobalBounds().height - mRenderTex.getSize().y
  };
  //ABs current offset
  mousePos += mCurrentOffset + (difference / 2.f);
  mousePos.x /= mRenderSprite.getScale().x;
  mousePos.y /= mRenderSprite.getScale().y;
  // mousePos -= static_cast<sf::Vector2i>(mTilesetManager.getTileset(mGui.activePage->texName).getSize()) / 2;
  std::cout << "MousePos on tileset: " << mousePos.x << " | " << mousePos.y << std::endl;
  auto tileSize = mSelectionManager.getSelection().tileSize;
  sf::Vector2i tile = {
    static_cast<int>(mousePos.x) / tileSize.x,
    static_cast<int>(mousePos.y) / tileSize.y
  };
  return tile;
}

void TilesetController::openLoadTilesetDialog()
{
  mGui.loadTilesetName->SetText("tileset.png");

  mGui.loadTilesetDialog->Show(true);
  mGui.loadTilesetDialog->GrabFocus();
}

void TilesetController::loadNewTileset()
{
  auto name = mGui.loadTilesetName->GetText();
  if (mTilesetManager.loadTileset(name))
  {
    addTilesetToView(name);
    mGui.loadTilesetDialog->Show(false);
    mGui.notebook->SetCurrentPage(mGui.notebook->GetPageCount() - 1);
    updateActiveCanvas();
  }
  else
  {
    mGui.loadTilesetName->SetText("Could not load the file");
  }
}

void TilesetController::updateActiveCanvas()
{
  auto activePage = mGui.notebook->GetCurrentPage();
  if (mGui.tilesetPages.size() != 0)
  {
    auto ptr = &mGui.tilesetPages[activePage];
    if (ptr != mGui.activePage)
    {
      mGui.activePage = ptr;
      mSelectionManager.setTextureIndex(mTilesetManager.getTilesetIndex(mGui.activePage->texName));
      mSelectionManager.setTexture(&mTilesetManager.getTileset(mGui.activePage->texName));
      redrawCanvas();
    }
  }
}

void TilesetController::updateZoom()
{
  std::string text = mGui.zoomEntry->GetText();
  if (text.size() > 0)
  {
    if (text.back() == '%')
      text.pop_back();
    mCurrentZoom = static_cast<float>(std::atof(text.c_str()));
    if (mCurrentZoom <= 0)
      mCurrentZoom = 1;
    else
      mCurrentZoom /= 100;

    mGui.zoomScale->SetValue(mCurrentZoom);
  }
}

void TilesetController::updateOffset()
{
  mCurrentOffset.x = mGui.activePage->hScrollbar->GetValue();
  mCurrentOffset.y = mGui.activePage->vScrollbar->GetValue();
}

void TilesetController::addTilesetToView(const std::string &name)
{
  auto label = sfg::Label::Create(name);
  auto box = sfg::Box::Create(sfg::Box::Orientation::VERTICAL);
  auto subBox = sfg::Box::Create();
  auto canvas = sfg::Canvas::Create();
  canvas->SetId(name);
  canvas->SetRequisition({ 200, 200 });
  canvas->GetSignal(sfg::Canvas::OnLeftClick).Connect(std::bind(&TilesetController::updateSelectedTile, this));
  subBox->Pack(canvas);
  auto vScrollbar = sfg::Scrollbar::Create(sfg::Scrollbar::Orientation::VERTICAL);
  vScrollbar->SetRequisition({ 18, 0 });
  vScrollbar->SetRange(0, 100);
  vScrollbar->SetIncrements(1, 5);
  vScrollbar->GetAdjustment()->GetSignal(sfg::Adjustment::OnChange).Connect(std::bind(&TilesetController::updateOffset, this));
  subBox->Pack(vScrollbar, false);
  auto hScrollbar = sfg::Scrollbar::Create();
  hScrollbar->SetRequisition({ 0, 18 });
  hScrollbar->SetIncrements(1, 5);
  hScrollbar->SetRange(0, 100);
  hScrollbar->GetAdjustment()->GetSignal(sfg::Adjustment::OnChange).Connect(std::bind(&TilesetController::updateOffset, this));
  box->Pack(subBox);
  box->Pack(hScrollbar, false);
  mGui.notebook->AppendPage(box, label);
  mGui.tilesetPages.push_back({ canvas, hScrollbar, vScrollbar, name });

  //Check if the preview page is still there, delete if so
  if (mGui.notebook->GetNthPage(0)->GetId() == "preview")
  {
    mGui.notebook->RemovePage(0);
  }
}

void TilesetController::initGui()
{
  initTilesetWindow();
  initLoadTilesetDialog();
}

void TilesetController::initTilesetWindow()
{
  auto box = sfg::Box::Create(sfg::Box::Orientation::VERTICAL);

  //TILESET view
  mGui.notebook = sfg::Notebook::Create();
  mGui.notebook->GetSignal(sfg::Notebook::OnLeftClick).Connect(std::bind(&TilesetController::updateActiveCanvas, this));
 // mGui.notebook->GetSignal(sfg::Notebook::OnSizeAllocate).Connect(std::bind(&TilesetController::redrawCanvas, this));
  
  auto label = sfg::Label::Create("No tileset loaded");
  auto canvas = sfg::Canvas::Create();
  canvas->SetRequisition({ 50.f, 50.f });
  canvas->SetId("preview");
  mGui.notebook->AppendPage(canvas, label);


  box->Pack(mGui.notebook);

  //CONTROLS
  auto subBox = sfg::Box::Create();
  box->Pack(subBox, false);

  auto bt = sfg::Button::Create("Add");
  bt->GetSignal(sfg::Button::OnLeftClick).Connect(std::bind(&TilesetController::openLoadTilesetDialog, this));
  subBox->Pack(bt, false);
  bt = sfg::Button::Create("Remove");
  subBox->Pack(bt, false);
  mGui.zoomEntry = sfg::Entry::Create("100%");
  mGui.zoomEntry->SetRequisition({ 50.f, 0.f });
  mGui.zoomEntry->GetSignal(sfg::Entry::OnTextChanged).Connect(std::bind(&TilesetController::updateZoom, this));
  subBox->Pack(mGui.zoomEntry, false);
  mGui.zoomScale = sfg::Scale::Create(0, 5, 0.1f);
  mGui.zoomScale->SetValue(1.f);
  mGui.zoomScale->SetRequisition({ 0, 10 });
  subBox->Pack(mGui.zoomScale);


  auto window = sfg::Window::Create(sfg::Window::Style::TOPLEVEL | sfg::Window::Style::SHADOW);
  window->GetSignal(sfg::Window::OnLeftClick).Connect([this](){ mUsedEvent = true; });
  window->SetTitle("Tilemaps");
  window->Add(box);
  mDesktop.Add(window);
}

void TilesetController::initLoadTilesetDialog()
{
  mGui.loadTilesetDialog = sfg::Window::Create(sfg::Window::Style::BACKGROUND |
    sfg::Window::Style::TITLEBAR);
  mGui.loadTilesetDialog->GetSignal(sfg::Window::OnLeftClick).Connect([this](){ mUsedEvent = true; });
  mGui.loadTilesetDialog->SetTitle("Load new Tileset");

  auto box = sfg::Box::Create(sfg::Box::Orientation::VERTICAL, 5.f);

  auto frame = sfg::Frame::Create("Enter tileset name with extension");
  mGui.loadTilesetName = sfg::Entry::Create("tileset.png");
  frame->Add(mGui.loadTilesetName);
  box->Pack(frame);

  auto subBox = sfg::Box::Create(sfg::Box::Orientation::HORIZONTAL, 5.f);
  auto bt = sfg::Button::Create("Load");
  bt->GetSignal(sfg::Button::OnLeftClick).Connect(std::bind(&TilesetController::loadNewTileset, this));
  subBox->Pack(bt);
  bt = sfg::Button::Create("Cancel");
  bt->GetSignal(sfg::Button::OnLeftClick).Connect([this](){mGui.loadTilesetDialog->Show(false); });
  subBox->Pack(bt);

  box->Pack(subBox);


  mGui.loadTilesetDialog->Add(box);
  mGui.loadTilesetDialog->Show(false);
  //mLoadTilesetDialog.window->SetZOrder(5);
  mDesktop.Add(mGui.loadTilesetDialog);
}