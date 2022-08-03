#pragma once

#include <SDL.h>
#include <vector>
#include <thread>
#include <queue>

template <typename arg1>
class IOCallback {
public:
	typedef void(*Func)(arg1);
};

class Game {

public:
	Game(const char* title, int width, int height) noexcept;
	~Game(void) noexcept;
	void Mainloop(void) noexcept;
	inline bool IsRunning(void) const noexcept { return mRunning; }
	inline void StopRunning(void) noexcept { mRunning = false; }

	inline SDL_Renderer* GetRenderer(void) noexcept { return mRenderer; }

	std::vector<IOCallback<SDL_Keycode>::Func> keydownCallbacks;
	std::vector<IOCallback<SDL_Keycode>::Func> keyupCallbacks;
	std::vector<IOCallback<Uint8>::Func> mousebuttondownCallbacks;
	std::vector<IOCallback<Uint8>::Func> mousebuttonupCallbacks;
	std::vector<IOCallback<Sint32>::Func> mousewheelCallbacks;

protected:
	void HandleEvents(void) noexcept;
	void Update(void) noexcept;
	void Render(void) const noexcept;

	const char* mTitle;
	int mWidth;
	int mHeight;
	SDL_Window* mWindow;
	SDL_Renderer* mRenderer;
	bool mRunning;
	
	SDL_Thread* mSimulationThread;
	SDL_Thread* mEventThread;
	std::queue<SDL_Event*> mEventQueue;
	
public:
	static inline void AttachSingleton(Game* newSingleton) noexcept
	{
		singleton = newSingleton;
	}

	static inline Game* GetSingleton(void) noexcept
	{
		return singleton;
	}

	static inline void DestroySingleton(void) noexcept
	{
		delete singleton;
		singleton = nullptr;
	}

private:
	static Game* singleton;

};