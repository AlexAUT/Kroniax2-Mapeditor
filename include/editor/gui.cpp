#include "gui.hpp"

#include "../application.hpp"

#include <SFML/Graphics/RenderWindow.hpp>

#include <SFGUI/Box.hpp>
#include <SFGUI/Button.hpp>
#include <SFGUI/Canvas.hpp>
#include <SFGUI/ComboBox.hpp>
#include <SFGUI/Frame.hpp>
#include <SFGUI/Image.hpp>
#include <SFGUI/Label.hpp>
#include <SFGUI/RadioButton.hpp>
#include <SFGUI/Scale.hpp>
#include <SFGUI/ScrolledWindow.hpp>
#include <SFGUI/ToggleButton.hpp>


Gui::Gui(Application &application) :
  mApplication(application)
{
  initGui();
}

bool Gui::handleEvent(const sf::Event &event)
{
  mDesktop.HandleEvent(event);

  return false;
}

void Gui::update(float seconds)
{
  mDesktop.Update(seconds);
}

void Gui::display()
{
  mApplication.mWindow.resetGLStates();
  mGui.Display(mApplication.mWindow);
}

sfg::Desktop& Gui::getDesktop()
{
  return mDesktop;
}

const sfg::Desktop& Gui::getDesktop() const
{
  return mDesktop;
}

void Gui::initGui()
{
  initMenuBar();
  initSelectionWindow();
}

void Gui::loadTileset()
{
  auto name = mLoadTilesetDialog.tilesetName->GetText();
  if (mApplication.mTilesetManager.loadTileset(name))
  {
    auto canvas = sfg::Canvas::Create(false);
    canvas->SetRequisition({ 100, 100 });
    canvas->GetSignal(sfg::Canvas::OnLeftClick).Connect(std::bind(&TilesetManager::clickedOnTileset, 
      &mApplication.mTilesetManager, std::ref(mApplication.mEvent), canvas, name));
    canvas->GetSignal(sfg::Canvas::OnSizeAllocate).Connect(std::bind(&TilesetManager::drawTextureOnCanvas,
      &mApplication.mTilesetManager, canvas, name));

    auto label = sfg::Label::Create(name);

    mTilesetNotebook->AppendPage(canvas, label);

    mLoadTilesetDialog.window->Show(false);

    mApplication.mTilesetManager.drawTextureOnCanvas(canvas, name);

    if (mTilesetNotebook->GetNthPage(0)->GetId() == "preview")
    {
      mTilesetNotebook->RemovePage(0);
    }
  }
  else
  {
    mLoadTilesetDialog.tilesetName->SetText("Failed to load tileset");
  }
}

void Gui::initMenuBar()
{
  auto box = sfg::Box::Create();
  box->SetSpacing(4.f);

  //Frame FILE
  auto frame = sfg::Frame::Create("File");
  auto subBox = sfg::Box::Create(sfg::Box::Orientation::HORIZONTAL, 4.f);

  auto bt = sfg::Button::Create("New");
  subBox->Pack(bt);
  bt = sfg::Button::Create("Save");
  subBox->Pack(bt);
  bt = sfg::Button::Create("Load");
  subBox->Pack(bt);
  frame->Add(subBox);
  box->Pack(frame);

  //Frame VIEW
  frame = sfg::Frame::Create("View");
  subBox = sfg::Box::Create(sfg::Box::Orientation::HORIZONTAL, 4.f);
  auto toogleButton = sfg::ToggleButton::Create("View grid");
  subBox->Pack(toogleButton);
  frame->Add(subBox);
  box->Pack(frame);

  //Add everything to window
  auto window = sfg::Window::Create(sfg::Window::Style::BACKGROUND | sfg::Window::Style::SHADOW);
  window->Add(box);
  mDesktop.Add(window);
}

void Gui::initSelectionWindow()
{
  auto box = sfg::Box::Create(sfg::Box::Orientation::VERTICAL);

  //ROTATION
  auto frame = sfg::Frame::Create("Rotation");
  auto subBox = sfg::Box::Create();
  frame->Add(subBox);

  auto radioButton = sfg::RadioButton::Create("0°");
  subBox->Pack(radioButton);
  radioButton->SetActive(true);
  radioButton = sfg::RadioButton::Create("90°", radioButton->GetGroup());
  subBox->Pack(radioButton);
  radioButton = sfg::RadioButton::Create("180°", radioButton->GetGroup());
  subBox->Pack(radioButton);
  radioButton = sfg::RadioButton::Create("270°", radioButton->GetGroup());
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
  sfImg.create(25, 25, { 255, 255, 255 });
  auto img = sfg::Image::Create(sfImg);
  frame->Add(img);

  box->Pack(frame, true);

  auto window = sfg::Window::Create(sfg::Window::Style::BACKGROUND | sfg::Window::Style::SHADOW |
    sfg::Window::Style::TITLEBAR);
  window->SetTitle("Drawing mode");
  window->Add(box);
  mDesktop.Add(window);
}

