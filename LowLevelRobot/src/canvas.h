#pragma once

#include "utils.h"

#include <SDL.h>

class Color {
public:
	Uint8 r, g, b, a;
	static const Color black;
	static const Color white;
	static const Color blue;
	static const Color yellow;
	static const Color red;
	static const Color green;
};

class Image {
public:
	Image(const char* filePath);
	~Image(void);
	inline SDL_Texture* GetTexture(void) { return mTexture; }
	void Render(const Rect& transform, const Rect& frame);
	void Render(const Rect& transform);
protected:
	SDL_Texture* mTexture;
};

class Canvas {

public:
	Canvas(SDL_Renderer* renderer) noexcept;

	inline void Clear(void) noexcept
	{
		SDL_RenderClear(mRenderer);
	}

	inline void Clear(const Color& color) noexcept
	{
		SetColor(color);
		Clear();
	}

	inline void Present(void) noexcept
	{
		SDL_RenderPresent(mRenderer);
	}

	inline void SetColor(const Color& color) noexcept
	{
		SDL_SetRenderDrawColor(mRenderer, color.r, color.g, color.b, color.a);
	}

	inline void FillRect(const Rect& rect) noexcept
	{
		SDL_Rect sdlRect = rect.ToSDLRect();
		SDL_RenderFillRect(mRenderer, &sdlRect);
	}

protected:
	SDL_Renderer* mRenderer;

public:

	static inline void AttachSingleton(Canvas* new_singleton) noexcept
	{
		singleton = new_singleton;
	}

	static inline Canvas* GetSingleton(void) noexcept
	{
		return singleton;
	}

	static inline void DestroySingleton(void) noexcept
	{
		delete singleton;
		singleton = nullptr;
	}

private:
	static Canvas* singleton;

};