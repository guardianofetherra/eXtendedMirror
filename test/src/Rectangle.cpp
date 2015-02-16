#include <Rectangle.hpp>

Rectangle::Rectangle(int x, int y, int w, int h)
	: Shape(x, y), width(w), height(h)
{
}

int Rectangle::getWidth()
{
	return width;
}

void Rectangle::setWidth(int w)
{
	width = w;
}

int Rectangle::getHeight()
{
	return height;
}

void Rectangle::setHeight(int h)
{
	height = h;
}