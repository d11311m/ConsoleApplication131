#include <iostream>
#include <chrono>
#include <thread>
#include <Windows.h>
#include <vector>
#include <conio.h>
#include <random>
#include "Zmeyka.h"
#include "color_factory.h"

#define RESET   "\033[0m"
#define BLACK   "\033[30m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN    "\033[36m"

using namespace std;

chrono::milliseconds time_delay(500);

string apple_color;

color_factory cf;

bool is_running = true;

COORD apple;

int score_display = 0;

HANDLE HND = GetStdHandle(STD_OUTPUT_HANDLE);

void score_update()
{
  score_display++;

  time_delay -= chrono::milliseconds(10);
}
void Coord_movment(COORD& coord, direction dir)
{
  switch (dir)
  {
  case direction::UP:
    coord.Y--;
    break;
  case direction::DOWN:
    coord.Y++;
    break;
  case direction::LEFT:
    coord.X--;
    break;
  case direction::RIGHT:
    coord.X++;
    break;
  }
}

void apple_create(vector<COORD> snake)
{
  int rand_w;
  int rand_h;

  random_device rd;
  uniform_int_distribution range_w(1, width - 2);
  uniform_int_distribution range_h(1, height - 2);

  bool must_continue = true;

  do
  {                         // 1.
    rand_w = range_w(rd);   // tow random numbers 
    rand_h = range_h(rd);   //

    must_continue = false;  // 3. using if everything is good 

    for (COORD element : snake) // where we taken the numbers from 
    {
      if (element.X == rand_w && element.Y == rand_h)  // 2. cheking the numbers
      {
        must_continue = true;  // if the coords are bad/(alredy using it) we start from the beginning
        break;
      }
    }
  } while (must_continue);

  apple.X = rand_w;
  apple.Y = rand_h;

  apple_color = cf.get_random_color();
}


Zmeyka zmeyka;

void keyboard_input()
{
  for ( int key = 0; is_running; key = _getch())
  {
    switch (key)
    {
    case 'w':
      zmeyka.future_Direction = direction::UP;
      break;
    case 's':
      zmeyka.future_Direction = direction::DOWN;
      break;
    case 'd':
      zmeyka.future_Direction = direction::RIGHT;
      break;
    case 'a':
      zmeyka.future_Direction = direction::LEFT;
      break;
    }
  }
}

void HideCursor()
{
  CONSOLE_CURSOR_INFO cursorInfo;
  GetConsoleCursorInfo(HND, &cursorInfo);
  cursorInfo.bVisible = false;
  SetConsoleCursorInfo(HND, &cursorInfo);
}

void draw_poole()
{
  for (int i = 0; i < height; i++)
  {
    for (int j = 0; j < width; j++)
    {
      if ((i==0||i==height-1||j == width - 1 || j == 0))
      {
        printf("#");
      }
      else 
      {
        printf(" ");
      }
    }
    printf("\n");
  } 
  cout << "\n\n\n" << "SCORE: " << score_display;
}


void check_gameover(vector <COORD> zmeyka_copy)
{
  if (zmeyka_copy[0].X == 0 || zmeyka_copy[0].Y == 0 ||
    zmeyka_copy[0].X == width - 1 || zmeyka_copy[0].Y == height - 1)
  {
    is_running = false;

    SetConsoleCursorPosition(HND, { width / 3 ,height / 2 });

    printf("\033[31mGAME OVER");
  }

  for (size_t i = 1; i < zmeyka_copy.size(); i++)
  {
    if (zmeyka_copy[i].X == zmeyka_copy[0].X && zmeyka_copy[i].Y == zmeyka_copy[0].Y)
    {
      is_running = false;
      SetConsoleCursorPosition(HND, { width / 3 ,height / 2 });
      printf("\033[31mGAME OVER");
    } 
  }
}

void apple_draw()
{
  SetConsoleCursorPosition(HND,apple);
  cout << apple_color << "o" << RESET;
}

int main()
{
  jthread keysActive(keyboard_input);
  
  HideCursor();
  
  
  apple_create(zmeyka.segment_coords);

  while (is_running)
  {
    //zmeyka.draw_current_direction();

    draw_poole();

    zmeyka.draw_segments();

    apple_draw();

    this_thread::sleep_for(time_delay);

    zmeyka.move();

    check_gameover(zmeyka.segment_coords);

    SetConsoleCursorPosition(HND,{0,0});
  }
}

/// get rid of lag
/// colours