#pragma once
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>

class Point
{
public:
	double x;
	double y;

	Point(double _x, double _y);
};

Point::Point(double _x, double _y)
{
	x = _x;
	y = _y;
}