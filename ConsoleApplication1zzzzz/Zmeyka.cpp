#include "Zmeyka.h"

Zmeyka::Zmeyka()
{
  COORD mid;
  mid.X = width / 2;
  mid.Y = height / 2;

  segment_coords.push_back(mid);

  mid.Y++;
  segment_coords.push_back(mid);

  mid.Y++;
  segment_coords.push_back(mid);

  mid.Y++;
  segment_coords.push_back(mid);
}

void Zmeyka::draw_current_direction()
{
  switch (future_Direction)
  {
  case direction::IN_PLACE:
    cout << "in place \n";
    break;
  case direction::UP:
    cout << "up       \n";
    break;
  case direction::DOWN:
    cout << "down     \n";
    break;
  case direction::LEFT:
    cout << "left     \n";
    break;
  case direction::RIGHT:
    cout << "right    \n";
    break;
  }
}

void Zmeyka::draw_segments()
{
  for (size_t i = 0; i < segment_coords.size(); i++)
  {
    SetConsoleCursorPosition(HND, segment_coords[i]);
    cout << "O";
  }
}

bool Zmeyka::is_future_direction_legal()
{
  COORD head = segment_coords[0];

  Coord_movment(head, future_Direction);

  if (head.X == segment_coords[1].X && head.Y == segment_coords[1].Y)
  {
    return false;
  }
  return true;
}

void Zmeyka::update_current_direction()
{
  if (is_future_direction_legal())
  {
    current_Direction = future_Direction;
  }
}

void Zmeyka::move()
{


  update_current_direction();

  COORD head = segment_coords[0];

  Coord_movment(head, current_Direction);
  if (head.Y == apple.Y && head.X == apple.X) // << apple eating
  {
    COORD tail;
    tail = segment_coords[segment_coords.size() - 1];

    for (size_t i = segment_coords.size() - 1; i > 0; i--)
    {
      segment_coords[i] = segment_coords[i - 1];
    }
    segment_coords[0] = head;

    segment_coords.push_back(tail);

    score_update();

    apple_create(segment_coords);
    return;
  }

  // i = хвост {только для первой итерации}

  for (size_t i = segment_coords.size() - 1; i > 0; i--)
  {
    segment_coords[i] = segment_coords[i - 1];
  }
  segment_coords[0] = head;

}
