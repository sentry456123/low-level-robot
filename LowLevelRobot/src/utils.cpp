#include "utils.h"

Vector2i::Vector2i(void) noexcept
	:
	x(0),
	y(0)
{
}

Vector2i::Vector2i(int x, int y) noexcept
	:
	x(x),
	y(y)
{
}

Vector2i::Vector2i(int xy) noexcept
	:
	x(xy),
	y(xy)
{
}

Rect::Rect(void) noexcept
	:
	position(Vector2i()),
	size(Vector2i())
{
}

Rect::Rect(const Vector2i& position, const Vector2i& size) noexcept
	:
	position(position),
	size(size)
{
}

Rect::Rect(int x, int y, int w, int h) noexcept
	:
	position(Vector2i(x, y)),
	size(Vector2i(w, h))
{
}
