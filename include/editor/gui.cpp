#include "gui.hpp"

#include "../application.hpp"

#include <SFML/Graphics/RenderWindow.hpp>

#include <SFGUI/Box.hpp>
#include <SFGUI/Button.hpp>
#include <SFGUI/Frame.hpp>
#include <SFGUI/ToggleButton.hpp>
#include <SFGUI/Window.hpp>


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

