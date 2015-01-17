#ifndef MOUSEONWINDOWCHECKER_HPP
#define MOUSEONWINDOWCHECKER_HPP

class MouseOnWindowChecker
{
public:
  static MouseOnWindowChecker& getInstance();

  void increaseCounter();
  void decreaseCounter();

  bool isMouseOnWidget();
  unsigned getCounter();

private:
  MouseOnWindowChecker();

private:
  unsigned mCounter;
};

#endif