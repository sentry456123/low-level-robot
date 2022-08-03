#include "game.h"

#include "canvas.h"
#include "scene.h"

#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <iostream>

#define FPS 30
#define SIMULATION_DELAY 200
#define EVENT_DELAY FPS

static int SimulationMainFunc(void* data)
{
    static int count = 0;
    while (Game::GetSingleton()->IsRunning()) {
        std::cout << "Hello Motherfuckdr " << count << std::endl;
        count++;
        SDL_Delay(SIMULATION_DELAY);
    }
    return 0;
}

static int EventMainFunc(void* data)
{
    auto eventQueue = (std::queue<SDL_Event*>*)data;
    Game* game = Game::GetSingleton();
    SDL_Event* e;
    SDL_Keycode key;
    Uint8 mouse;
    Sint32 wheel;

    while (Game::GetSingleton()->IsRunning()) {
        if (eventQueue->empty()) {
            SDL_Delay(EVENT_DELAY);
        } else {
            e = eventQueue->front();
            key = e->key.keysym.sym;
            mouse = e->button.button;
            wheel = e->wheel.y;
            switch (e->type) {
            case SDL_KEYDOWN:
                for (auto callback : game->keydownCallbacks) {
                    callback(key);
                }
            case SDL_KEYUP:
                for (auto callback : game->keyupCallbacks) {
                    callback(key);
                }
            case SDL_MOUSEBUTTONDOWN:
                for (auto callback : game->mousebuttondownCallbacks) {
                    callback(mouse);
                }
            case SDL_MOUSEBUTTONUP:
                for (auto callback : game->mousebuttonupCallbacks) {
                    callback(mouse);
                }
            case SDL_MOUSEWHEEL:
                for (auto callback : game->mousewheelCallbacks) {
                    callback(wheel);
                }
                break;
            case SDL_QUIT:
                Game::GetSingleton()->StopRunning();
                break;
            }
            delete e;
            eventQueue->pop();
        }
    }
    return 0;
}

static void ShoeErrorMessageBox(const char* title) noexcept
{
    SDL_ShowSimpleMessageBox(
        SDL_MESSAGEBOX_ERROR,
        title, SDL_GetError(), nullptr
    );
}

static void QuitCallback(SDL_Keycode key) noexcept
{
    if (key == SDLK_ESCAPE) {
        Game::GetSingleton()->StopRunning();
    }
}

Game::Game(const char* title, int width, int height) noexcept
	:
	mTitle(title),
	mWidth(width),
	mHeight(height)
{
    std::cout << "Initializing SDL..." << std::endl;
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO)) {
        ShoeErrorMessageBox(mTitle);
        std::exit(EXIT_FAILURE);
    }

    std::cout << "Initializing SDL_ttf..." << std::endl;
    if (TTF_Init()) {
        ShoeErrorMessageBox(mTitle);
        std::exit(EXIT_FAILURE);
    }

    std::cout << "Initializing SDL_image..." << std::endl;
    if (!IMG_Init(IMG_INIT_PNG)) {
        ShoeErrorMessageBox(mTitle);
        std::exit(EXIT_FAILURE);
    }

    std::cout << "Initializing SDL_mixer..." << std::endl;
    if (!Mix_Init(MIX_INIT_MP3)) {
        ShoeErrorMessageBox(mTitle);
    }

    std::cout << "Creating a window..." << std::endl;
    mWindow = SDL_CreateWindow(
        mTitle, 
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        mWidth, mHeight, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE
    );
    if (!mWindow) {
        ShoeErrorMessageBox(mTitle);
        std::exit(EXIT_FAILURE);
    }

    std::cout << "Creating a renderer..." << std::endl;
    mRenderer = SDL_CreateRenderer(
        mWindow, -1,
        SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED
    );
    if (!mRenderer) {
        ShoeErrorMessageBox(mTitle);
        std::exit(EXIT_FAILURE);
    }

    mRunning = true;

    std::cout << "Setting keybinds..." << std::endl;
    keydownCallbacks.push_back(QuitCallback);

    std::cout << "Creating threads..." << std::endl;
    mSimulationThread = SDL_CreateThread(SimulationMainFunc, "Simulation Thread", nullptr);
    mEventThread = SDL_CreateThread(EventMainFunc, "Event Thread", &mEventQueue);

    std::cout << "Creating a scene..." << std::endl;
    Scene::AttachSingleton(new Scenes::Opening());

    std::cout << "Initialization finished" << std::endl;
}

Game::~Game(void) noexcept
{
    std::cout << "Finalizing..." << std::endl;
    SDL_DetachThread(mSimulationThread);
    SDL_DetachThread(mEventThread);
    Scene::DestroySingleton();
    SDL_DestroyRenderer(mRenderer);
    SDL_DestroyWindow(mWindow);
    Mix_Quit();
    IMG_Quit();
    TTF_Quit();
    SDL_Quit();
    std::cout << "Finalization finished" << std::endl;
}

void Game::Mainloop(void) noexcept
{
    Uint64 start, end;
    Sint64 delay;

    while (mRunning) {
        start = SDL_GetTicks64();
        HandleEvents();
        Render();
        end = SDL_GetTicks64();
        delay = 1000 / FPS - (end - start);
        std::cout << "Delay: " << delay << std::endl;
        if (delay > 0) {
           SDL_Delay(delay);
        }
    }
}

void Game::HandleEvents(void) noexcept
{
    SDL_Event e;
    SDL_PollEvent(&e);
    mEventQueue.push(new SDL_Event(e));
}

void Game::Update(void) noexcept
{
    Scene::GetSingleton()->Update();
}

void Game::Render(void) const noexcept
{
    Canvas* canvas = Canvas::GetSingleton();
    Scene::GetSingleton()->Render();
    canvas->Present();
}

Game* Game::singleton;