#include "scene.h"

#include "canvas.h"

Scene::Scene(void) noexcept {}

Scene::~Scene(void) noexcept {}

void Scenes::Opening::Update(void) noexcept
{
	
}

void Scenes::Opening::Render(void) const noexcept
{
	Canvas* canvas = Canvas::GetSingleton();
	canvas->Clear(Color::blue);
	canvas->SetColor(Color::green);
	canvas->FillRect(Rect(100, 100, 100, 100));
}

Scene* Scene::singleton = nullptr;