#pragma once
#include "jhScene.h"

namespace jh
{
	class SceneManager
	{
	public:
		static void Initalize();
		static void Update();
		static void FixedUpdate();
		static void Render();
		static void Destroy();
		static void Release();

		static void LoadScene(eSceneType type);
		static Scene* GetActiveScene() { return mActiveScene; }

		static void   SetActiveScene(Scene* activescene) { mActiveScene = activescene; }

	private:
		static std::vector<Scene*> mScenes;
		static Scene* mActiveScene;
	};
}
