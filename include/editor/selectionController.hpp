#ifndef SELECTION_CONTROLLER_HPP
#define SELECTION_CONTROLLER_HPP

#include <memory>

class SelectionManager;

namespace sfg
{
  class Desktop;
}

class SelectionController
{
public:
  SelectionController(SelectionManager &selectionManager, sfg::Desktop &desktop);
private:

  void initGui();

private:
  SelectionManager &mSelectionManager;
  sfg::Desktop &mDesktop;
};

#endif