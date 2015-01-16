#include "selectionController.hpp"

#include "selectionManager.hpp"

#include <SFGUI/Box.hpp>
#include <SFGUI/Desktop.hpp>
#include <SFGUI/Frame.hpp>
#include <SFGUI/Label.hpp>
#include <SFGUI/RadioButton.hpp>
#include <SFGUI/Scale.hpp>  
#include <SFGUI/Window.hpp>

SelectionController::SelectionController(SelectionManager &selectionManager, sfg::Desktop &desktop) :
  mSelectionManager(selectionManager),
  mDesktop(desktop)
{
  initGui();
}

void SelectionController::initGui()
{
  auto box = sfg::Box::Create(sfg::Box::Orientation::VERTICAL);

  //ROTATION
  auto frame = sfg::Frame::Create("Rotation");
  auto subBox = sfg::Box::Create();
  frame->Add(subBox);

  auto radioButton = sfg::RadioButton::Create("0°");
  radioButton->GetSignal(sfg::RadioButton::OnToggle).Connect([this, radioButton](){
    if (radioButton->IsActive())
      mSelectionManager.setRotation(0);
  });
  subBox->Pack(radioButton);
  radioButton->SetActive(true);
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
//  frame = sfg::Frame::Create("Preview tile");
//  sfImg.create(25, 25, { 255, 255, 255 });
//  auto img = sfg::Image::Create(sfImg);
//  frame->Add(img);

 // box->Pack(frame, true);

  auto window = sfg::Window::Create(sfg::Window::Style::BACKGROUND | sfg::Window::Style::SHADOW |
    sfg::Window::Style::TITLEBAR);
  window->SetTitle("Drawing mode");
  window->Add(box);
  mDesktop.Add(window);
}