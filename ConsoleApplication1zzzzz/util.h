#pragma once
#include <Windows.h>

inline bool are_coords_the_same(COORD first, COORD second)
{
	if (first.X == second.X && first.Y == second.Y)                            
	{
		return true;
	}
	return false;
}