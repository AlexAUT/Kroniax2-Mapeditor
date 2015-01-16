#ifndef SELECTION_CONTROLLER_HPP
#define SELECTION_CONTROLLER_HPP

#include <memory>

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>

class SelectionManager;

namespace sfg
{
  class Desktop;
  class Canvas;
}

class SelectionController
{
public:
  SelectionController(SelectionManager &selectionManager, sfg::Desktop &desktop,
    bool &usedEvent);

  void update();
  void redrawCanvas();
private:

  void initGui();

private:
  SelectionManager &mSelectionManager;
  sfg::Desktop &mDesktop;
  bool &mUsedEvent;

  std::shared_ptr<sfg::Canvas> mPreviewCanvas;
  sf::Sprite mTilePreview;
  sf::Texture mSampleTexture;

};

#endif