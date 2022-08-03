#pragma once

class Scene {
public:
	Scene(void) noexcept;
	~Scene(void) noexcept;
	virtual void Update(void) noexcept abstract;
	virtual void Render(void) const noexcept abstract;
protected:
public:
	static inline void AttachSingleton(Scene* newSingleton) noexcept
	{
		singleton = newSingleton;
	}

	static inline Scene* GetSingleton(void) noexcept
	{
		return singleton;
	}

	static inline void DestroySingleton(void) noexcept
	{
		delete singleton;
		singleton = nullptr;
	}

	static inline void ChangeSingleton(Scene* newSingleton) noexcept
	{
		delete singleton;
		singleton = newSingleton;
	}

private:
	static Scene* singleton;
};

namespace Scenes {
	class Opening : public Scene {
	public:
		virtual void Update(void) noexcept override;
		virtual void Render(void) const noexcept override;
	protected:
	};
}