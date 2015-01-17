#include "layerController.hpp"

#include "layerManager.hpp"
#include "selectionManager.hpp"

#include <SFGUI/Alignment.hpp>
#include <SFGUI/Box.hpp>
#include <SFGUI/Button.hpp>
#include <SFGUI/CheckButton.hpp>
#include <SFGUI/Desktop.hpp>
#include <SFGUI/Entry.hpp>
#include <SFGUI/Frame.hpp>
#include <SFGUI/Label.hpp>
#include <SFGUI/RadioButton.hpp>
#include <SFGUI/RadioButtonGroup.hpp>
#include <SFGUI/ScrolledWindow.hpp>
#include <SFGUI/Table.hpp>
#include <SFGUI/ToggleButton.hpp>
#include <SFGUI/Window.hpp>

LayerController::LayerController(LayerManager &layerManager, SelectionManager &selectionManager, TilesetManager &tilesetManager, sfg::Desktop &desktop,
  bool &usedEvent) :
  mLayerManager(layerManager),
  mSelectionManager(selectionManager),
  mTilesetManager(tilesetManager),
  mDesktop(desktop),
  mUsedEvent(usedEvent)
{
  initGui();
}

void LayerController::changeActiveLayer(const std::string &name)
{
   mLayerManager.setActiveLayer(name);
   mSelectionManager.setTileSize(mLayerManager.getActiveLayer().getTileSize());
   std::cout << "active layer: " << mLayerManager.getActiveLayerName() << std::endl;
}

void LayerController::initGui()
{
  initLayerWindow();
  initNewLayerDialog();
}

void LayerController::addLayer()
{
  auto name = mGui.newLayerName->GetText();
  int tileSizeX = std::atoi(mGui.newLayerTileSizeX->GetText().toAnsiString().c_str());
  int tileSizeY = std::atoi(mGui.newLayerTileSizeY->GetText().toAnsiString().c_str());

  if (mLayerManager.addLayer(name, { tileSizeX, tileSizeY }, mTilesetManager))
  {
    addLayerToTable(name);
  }
  else
  {
    mGui.newLayerName->SetText("Could not create the layer");
  }
}

void LayerController::addLayerToTable(const std::string &name)
{
  static auto group = sfg::RadioButtonGroup::Create();

  auto selected = sfg::RadioButton::Create(name, group);
  selected->GetSignal(sfg::RadioButton::OnToggle).Connect([this, selected, name](){
    if (selected->IsActive())
      changeActiveLayer(name);
  });
  selected->SetActive(true);

  auto visible = sfg::CheckButton::Create("");
  visible->SetActive(true);
  visible->GetSignal(sfg::CheckButton::OnToggle).Connect([this, name](){
    mLayerManager.getLayer(name).toggleVisible();
  });
  auto alig_visible = sfg::Alignment::Create();
  alig_visible->Add(visible);
  alig_visible->SetScale({ 0.f, 0.f });
  alig_visible->SetAlignment({ 0.5f, 0.5f });

  auto locked = sfg::CheckButton::Create("");
  locked->SetActive(false);
  locked->GetSignal(sfg::CheckButton::OnToggle).Connect([this, name](){
    mLayerManager.getLayer(name).toggleLocked();
  });
  auto alig_locked = sfg::Alignment::Create();
  alig_locked->Add(locked);
  alig_locked->SetScale({ 0.f, 0.f });
  alig_locked->SetAlignment({ 0.5f, 0.5f });

  mGui.layerTable->Attach(selected, { 0, mGui.tableRowCount, 1, 1 });
  mGui.layerTable->Attach(alig_visible, { 1, mGui.tableRowCount, 1, 1 });
  mGui.layerTable->Attach(alig_locked, { 2, mGui.tableRowCount, 1, 1 });
  mGui.tableRowCount++;
}

void LayerController::initLayerWindow()
{
  auto box = sfg::Box::Create(sfg::Box::Orientation::VERTICAL, 4.f);

  auto scrolledWindow = sfg::ScrolledWindow::Create();
  //scrolledWindow->SetRequisition({ 300, 50 });

  mGui.layerTable = sfg::Table::Create();
  auto label = sfg::Label::Create("Select Layer");
  mGui.layerTable->Attach(label, { 0, 0, 1, 1 }, 3, 3, { 15.f, 5.f });
  label = sfg::Label::Create("Visible");
  mGui.layerTable->Attach(label, { 1, 0, 1, 1 }, 3, 3, { 15.f, 5.f });
  label = sfg::Label::Create("Locked");
  mGui.layerTable->Attach(label, { 2, 0, 1, 1 }, 3, 3, { 15.f, 5.f });
  mGui.layerTable->SetColumnSpacings(2.f);
  mGui.layerTable->SetRowSpacings(2.f);
  
  mGui.tableRowCount = 1;
  
  
  scrolledWindow->AddWithViewport(mGui.layerTable);


  box->Pack(scrolledWindow, true);

  auto subBox = sfg::Box::Create();
  box->Pack(subBox, false);

  auto bt = sfg::Button::Create("Add");
  bt->GetSignal(sfg::Button::OnLeftClick).Connect([this](){mGui.newLayerDialog->Show(true); });
  subBox->Pack(bt, false);
  bt = sfg::Button::Create("Remove");
  subBox->Pack(bt, false);
  bt = sfg::Button::Create("Up");
  subBox->Pack(bt, false);
  bt = sfg::Button::Create("Down");
  subBox->Pack(bt, false);

  auto window = sfg::Window::Create(sfg::Window::Style::BACKGROUND | sfg::Window::Style::SHADOW |
    sfg::Window::Style::TITLEBAR | sfg::Window::Style::RESIZE);
  window->GetSignal(sfg::Window::OnMouseLeftPress).Connect([this](){ mUsedEvent = true; });
  window->GetSignal(sfg::Window::OnMouseMove).Connect([this](){ mUsedEvent = true; });

  window->Add(box);
  window->SetTitle("Layers");
  mDesktop.Add(window);
}

void LayerController::initNewLayerDialog()
{
  auto box = sfg::Box::Create(sfg::Box::Orientation::VERTICAL, 6.f);
  
  auto propertyFrame = sfg::Frame::Create("Layer properties");
  auto propertyBox = sfg::Box::Create(sfg::Box::Orientation::VERTICAL, 4.f);
  propertyFrame->Add(propertyBox);

  auto frame = sfg::Frame::Create("Layername");
  mGui.newLayerName = sfg::Entry::Create("untitled");
  frame->Add(mGui.newLayerName);
  propertyBox->Pack(frame);
  
  frame = sfg::Frame::Create("Tilesize (width|height)");
  mGui.newLayerTileSizeX = sfg::Entry::Create("25");
  mGui.newLayerTileSizeY = sfg::Entry::Create("25");
  auto subBox = sfg::Box::Create(sfg::Box::Orientation::HORIZONTAL, 10.f);
  subBox->Pack(mGui.newLayerTileSizeX);
  subBox->Pack(mGui.newLayerTileSizeY);
  frame->Add(subBox);
  propertyBox->Pack(frame);

  box->Pack(propertyFrame);

  subBox = sfg::Box::Create(sfg::Box::Orientation::HORIZONTAL, 5.f);
  auto bt = sfg::Button::Create("Create");
  bt->GetSignal(sfg::Button::OnLeftClick).Connect(std::bind(&LayerController::addLayer, this));
  subBox->Pack(bt);
  bt = sfg::Button::Create("Cancel");
  bt->GetSignal(sfg::Button::OnLeftClick).Connect([this](){mGui.newLayerDialog->Show(false); });
  subBox->Pack(bt);
  box->Pack(subBox);

  mGui.newLayerDialog = sfg::Window::Create(sfg::Window::Style::BACKGROUND |
    sfg::Window::Style::SHADOW | sfg::Window::Style::TITLEBAR);
  mGui.newLayerDialog->GetSignal(sfg::Window::OnMouseLeftPress).Connect([this](){ mUsedEvent = true; });
  mGui.newLayerDialog->GetSignal(sfg::Window::OnMouseMove).Connect([this](){ mUsedEvent = true; });
  mGui.newLayerDialog->SetTitle("Create new Layer");
  mGui.newLayerDialog->Add(box);
  mDesktop.Add(mGui.newLayerDialog);
}