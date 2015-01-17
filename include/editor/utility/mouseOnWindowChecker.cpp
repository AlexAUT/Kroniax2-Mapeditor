#include "mouseOnWindowChecker.hpp"

MouseOnWindowChecker::MouseOnWindowChecker() :
mCounter(0)
{

}

MouseOnWindowChecker& MouseOnWindowChecker::getInstance()
{
  static MouseOnWindowChecker instance;
  return instance;
}

void MouseOnWindowChecker::increaseCounter()
{
  mCounter++;
}

void MouseOnWindowChecker::decreaseCounter()
{
  if (mCounter > 0)
    mCounter--;
}

bool MouseOnWindowChecker::isMouseOnWidget()
{
  return mCounter > 0;
}

unsigned MouseOnWindowChecker::getCounter()
{
  return mCounter;
}