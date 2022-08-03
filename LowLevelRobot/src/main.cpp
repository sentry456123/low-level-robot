#include "game.h"
#include "canvas.h"

static void CreateSingleton(void) noexcept
{
	Game::AttachSingleton(new Game("Low Level Robot", 1280, 720));
	Canvas::AttachSingleton(new Canvas(Game::GetSingleton()->GetRenderer()));
}

static void DestroySingleton(void) noexcept
{
	Canvas::DestroySingleton();
	Game::DestroySingleton();
}

int main(int argc, char** argv)
{
	CreateSingleton();
	Game::GetSingleton()->Mainloop();
	DestroySingleton();
	return 0;
}