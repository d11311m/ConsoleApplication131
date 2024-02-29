#pragma once
#include <string>
#include <random>

using namespace std;

 class color_factory
{
public: 
	string get_random_color();

	color_factory();

	random_device rd;
	uniform_int_distribution<int> range{ 1,3 };
};