#include "selectionController.hpp"

#include "selectionManager.hpp"

#include <SFML/Graphics/Image.hpp>

#include <SFGUI/Alignment.hpp>
#include <SFGUI/Box.hpp>
#include <SFGUI/Canvas.hpp>
#include <SFGUI/Desktop.hpp>
#include <SFGUI/Frame.hpp>
#include <SFGUI/Label.hpp>
#include <SFGUI/RadioButton.hpp>
#include <SFGUI/Scale.hpp>  
#include <SFGUI/Window.hpp>

SelectionController::SelectionController(SelectionManager &selectionManager, sfg::Desktop &desktop,
    bool &usedEvent) :
  mSelectionManager(selectionManager),
  mDesktop(desktop),
  mUsedEvent(usedEvent)
{
  initGui();

  sf::Image img;
  img.create(25, 25, { 0, 0, 0 });
  mSampleTexture.loadFromImage(img);
}

void SelectionController::update()
{
  auto selection = mSelectionManager.getSelection();

  if (selection.texIndex >= 0)
  {
    if (selection.selectedTile.x >= 0 && selection.selectedTile.y >= 0)
    {
      mTilePreview.setTextureRect({
        selection.selectedTile.x * selection.tileSize.x,
        selection.selectedTile.y * selection.tileSize.y,
        selection.tileSize.x, selection.tileSize.y
      });
      mTilePreview.setTexture(*selection.tex);
      mTilePreview.setOrigin({ mTilePreview.getGlobalBounds().width / 2, mTilePreview.getGlobalBounds().height / 2 });
      mTilePreview.setPosition(mTilePreview.getOrigin());
      mTilePreview.setRotation(selection.rotation);
      mPreviewCanvas->SetRequisition({ static_cast<float>(selection.tileSize.x),
        static_cast<float>(selection.tileSize.y) });
    }
    else
    {
      mTilePreview.setTexture(mSampleTexture);
      mPreviewCanvas->SetRequisition({ 25.f, 25.f });
    }
  }
  else
  {
    mTilePreview.setTexture(mSampleTexture);
    mPreviewCanvas->SetRequisition({ 25.f, 25.f });
  }
  redrawCanvas();
}

void SelectionController::redrawCanvas()
{
  mPreviewCanvas->Clear();
  mPreviewCanvas->Draw(mTilePreview);
  mPreviewCanvas->Display();
}

void SelectionController::initGui()
{
  auto box = sfg::Box::Create(sfg::Box::Orientation::VERTICAL);

  //ROTATION
  auto frame = sfg::Frame::Create("Rotation");
  auto subBox = sfg::Box::Create();
  frame->Add(subBox);

  auto radioButton = sfg::RadioButton::Create("0°");
  radioButton->SetActive(true);
  radioButton->GetSignal(sfg::RadioButton::OnToggle).Connect([this, radioButton](){
    if (radioButton->IsActive())
      mSelectionManager.setRotation(0);
  });
  subBox->Pack(radioButton);
  radioButton = sfg::RadioButton::Create("90°", radioButton->GetGroup());
  radioButton->GetSignal(sfg::RadioButton::OnToggle).Connect([this, radioButton](){
    if (radioButton->IsActive())
      mSelectionManager.setRotation(90);
  });
  subBox->Pack(radioButton);
  radioButton = sfg::RadioButton::Create("180°", radioButton->GetGroup());
  radioButton->GetSignal(sfg::RadioButton::OnToggle).Connect([this, radioButton](){
    if (radioButton->IsActive())
      mSelectionManager.setRotation(180);
  });
  subBox->Pack(radioButton);
  radioButton = sfg::RadioButton::Create("270°", radioButton->GetGroup());
  radioButton->GetSignal(sfg::RadioButton::OnToggle).Connect([this, radioButton](){
    if (radioButton->IsActive())
      mSelectionManager.setRotation(270);
  });
  subBox->Pack(radioButton);

  box->Pack(frame, false);

  //TILE-COLOR
  frame = sfg::Frame::Create("Tile color");
  subBox = sfg::Box::Create(sfg::Box::Orientation::VERTICAL, 3.f);

  auto subsubBox = sfg::Box::Create();
  auto label = sfg::Label::Create("Red:");
  label->SetRequisition({ 45.f, 0.f });
  auto scale = sfg::Scale::Create(0, 255, 1);
  subsubBox->Pack(label, false);
  subsubBox->Pack(scale);
  subBox->Pack(subsubBox);

  subsubBox = sfg::Box::Create();
  label = sfg::Label::Create("Green:");
  label->SetRequisition({ 45.f, 0.f });
  scale = sfg::Scale::Create(0, 255, 1);
  subsubBox->Pack(label, false);
  subsubBox->Pack(scale);
  subBox->Pack(subsubBox);

  subsubBox = sfg::Box::Create();
  label = sfg::Label::Create("Blue:");
  label->SetRequisition({ 45.f, 0.f });
  scale = sfg::Scale::Create(0, 255, 1);
  subsubBox->Pack(label, false);
  subsubBox->Pack(scale);
  subBox->Pack(subsubBox);

  frame->Add(subBox);

  box->Pack(frame, false);

  //PREVIEW
  frame = sfg::Frame::Create("Preview tile");
  mPreviewCanvas = sfg::Canvas::Create();
  mPreviewCanvas->SetRequisition({ 25, 25 });
  auto align = sfg::Alignment::Create();
  align->SetScale({ 0.f, 0.f });
  align->SetAlignment({ 0.5f, 0.5f });
  align->Add(mPreviewCanvas);
  frame->Add(align);

  box->Pack(frame, false, false);

  auto window = sfg::Window::Create(sfg::Window::Style::BACKGROUND | sfg::Window::Style::SHADOW |
    sfg::Window::Style::TITLEBAR);
  window->GetSignal(sfg::Window::OnMouseLeftPress).Connect([this](){ mUsedEvent = true; });
  window->GetSignal(sfg::Window::OnMouseMove).Connect([this](){ mUsedEvent = true; });
  window->SetTitle("Drawing mode");
  window->Add(box);
  mDesktop.Add(window);
}