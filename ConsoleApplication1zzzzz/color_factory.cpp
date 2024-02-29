#include "color_factory.h"
#define RESET   "\033[0m"
#define BLACK   "\033[30m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN    "\033[36m"

string color_factory::get_random_color()
{
  int i = range(rd);

  switch (i)
  {
  case 1:
    return GREEN;
    break;
  case 2:
    return YELLOW;
    break;
  case 3:
    return RED;
    break;
  }
  return string(BLACK);
}

color_factory::color_factory()
{
  
}

