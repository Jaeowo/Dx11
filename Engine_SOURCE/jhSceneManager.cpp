#include "jhSceneManager.h"
#include "jhTransform.h"
#include "jhMeshRenderer.h"
#include "jhRenderer.h"
#include "jhResources.h"
#include "jhTexture.h"
#include "jhPlayerScript.h"
#include "jhCamera.h"
#include "jhCameraScript.h"
#include "jhSpriteRenderer.h"
#include "jhGridScript.h"
#include "jhObject.h"
#include "jhFadeInScript.h"
#include "jhFadeOutScript.h"
#include "jhTitleScene.h"
#include "jhPlayScene.h"
#include "jhCaveScene.h"
#include "jhCaveScene2.h"
#include "jhJungleScene.h"

namespace jh
{
	std::vector<Scene*> SceneManager::mScenes = {};
	Scene* SceneManager::mActiveScene = nullptr;

	void SceneManager::Initalize()
	{
		mScenes.resize((UINT)eSceneType::End);

		mScenes[(UINT)eSceneType::Title] = new TitleScene();
		mScenes[(UINT)eSceneType::Play] = new PlayScene();
		mScenes[(UINT)eSceneType::Cave] = new CaveScene();
		mScenes[(UINT)eSceneType::Cave2] = new CaveScene2();
		mScenes[(UINT)eSceneType::Jungle] = new JungleScene();

		mActiveScene = mScenes[(UINT)eSceneType::Title];

		for (Scene* scene : mScenes)
		{
			scene->Initalize();
		}
	}

	void SceneManager::Update()
	{
		mActiveScene->Update();
	}

	void SceneManager::FixedUpdate()
	{
		mActiveScene->FixedUpdate();
	}

	void SceneManager::Render()
	{
		mActiveScene->Render();
	}
	void SceneManager::Destroy()
	{
		mActiveScene->Destroy();
	}
	void SceneManager::Release()
	{
		mActiveScene = nullptr;
		for (Scene* scene : mScenes)
		{
			delete scene;
			scene = nullptr;
		}
	}
	void SceneManager::LoadScene(eSceneType type)
	{

		if (mActiveScene)
		{
			mActiveScene->OnExit();
		}
		

		std::vector<GameObject*> gameObjs
			= mActiveScene->GetDontDestroyGameObjects();
		mActiveScene = mScenes[(UINT)type];

		for (GameObject* obj : gameObjs)
		{
			eLayerType savedType = obj->GetLayerType();
			mActiveScene->AddGameObject(obj, savedType);
		}

		mActiveScene->OnEnter();
		//mActiveScene->Initalize();
	}
}