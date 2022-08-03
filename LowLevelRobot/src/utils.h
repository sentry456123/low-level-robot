#pragma once

#include <SDL.h>

class Vector2i {
public:
	int x;
	int y;

	Vector2i(void) noexcept;
	Vector2i(int x, int y) noexcept;
	Vector2i(int xy) noexcept;
};

class Rect {
public:
	Vector2i position;
	Vector2i size;

	Rect(void) noexcept;
	Rect(const Vector2i& position, const Vector2i& size) noexcept;
	Rect(int x, int y, int w, int h) noexcept;

	inline int GetX(void) const noexcept { return position.x; }
	inline int GetY(void) const noexcept { return position.y; }
	inline int GetW(void) const noexcept { return size.x; }
	inline int GetH(void) const noexcept { return size.y; }

	inline SDL_Rect ToSDLRect(void) const noexcept
	{
		SDL_Rect result;
		result.x = GetX();
		result.y = GetY();
		result.w = GetW();
		result.h = GetH();
		return result;
	}
};