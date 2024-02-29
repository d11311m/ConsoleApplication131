#pragma once
#include <vector>
#include <Windows.h>
#include <iostream>

using namespace std;

inline const int width = 40;
inline const int height = 20;

extern COORD apple;
extern HANDLE HND;
enum class direction
{
    IN_PLACE,
    UP,
    DOWN,
    LEFT,
    RIGHT,
};

void Coord_movment(COORD& coord, direction dir);
void apple_create(vector<COORD> snake);
void score_update();

class Zmeyka
{
public:

    vector<COORD> segment_coords;

    direction current_Direction = direction::UP;

    direction future_Direction = direction::UP;

    Zmeyka(); // << конструктор 
 
    void draw_current_direction(); // << test 
   
    void draw_segments();
 
    bool is_future_direction_legal();
 
    void update_current_direction();

    void move();
};

