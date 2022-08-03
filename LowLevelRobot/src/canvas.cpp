#include "canvas.h"

#include "game.h"

#include <SDL_image.h>
#include <iostream>

Image::Image(const char* filePath)
	:
	mTexture(nullptr)
{
	SDL_Surface* surface = IMG_Load(filePath);
	if (!surface) {
		std::cout << "Couldn't create surface from " << filePath << std::endl;
		return;
	}
	mTexture = SDL_CreateTextureFromSurface(Game::GetSingleton()->GetRenderer(), surface);
	if (!mTexture) {
		std::cout << "Couldn't create texture from " << filePath << std::endl;
		return;
	}
	SDL_FreeSurface(surface);
}

Image::~Image(void)
{
	SDL_DestroyTexture(mTexture);
}

void Image::Render(const Rect& transform, const Rect& frame)
{
	SDL_Rect transformRect = transform.ToSDLRect();
	SDL_Rect frameRect = frame.ToSDLRect();
	SDL_RenderCopy(Game::GetSingleton()->GetRenderer(), mTexture, &frameRect, &transformRect);
}

void Image::Render(const Rect& transform)
{
	SDL_Rect rect = transform.ToSDLRect();
	SDL_RenderCopy(Game::GetSingleton()->GetRenderer(), mTexture, nullptr, &rect);
}

Canvas::Canvas(SDL_Renderer* renderer) noexcept
	:
	mRenderer(renderer)
{
}

const Color Color::black = { 0x00, 0x00, 0x00, 0xff };
const Color Color::white = { 0xff, 0xff, 0xff, 0xff };
const Color Color::blue = { 0x00, 0x00, 0xff, 0xff };
const Color Color::yellow = { 0xff, 0xff, 0x00, 0xff };
const Color Color::red = { 0xff, 0x00, 0x00, 0xff };
const Color Color::green = { 0x00, 0xff, 0x00, 0xff };
Canvas* Canvas::singleton = nullptr;
