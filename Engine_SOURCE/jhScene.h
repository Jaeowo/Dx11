#pragma once
#include "jhEntity.h"
#include "jhLayer.h"
#include "jhGameObject.h"

namespace jh
{
	using namespace jh::enums;
	class Scene : public Entity
	{
	public:
		Scene(eSceneType type);
		virtual ~Scene();

		virtual void Initalize();
		virtual void Update();
		virtual void FixedUpdate();
		virtual void Render();

		virtual void OnEnter();
		virtual void OnExit();
		virtual void Destroy();

		eSceneType GetSceneType() { return mType; }
		void AddGameObject(GameObject* gameObj, const eLayerType type);
		Layer& GetLayer(eLayerType type) { return mLayers[(UINT)type]; }
		std::vector<GameObject*> GetDontDestroyGameObjects();

	private:
		std::vector<Layer> mLayers;
		eSceneType mType;
	};
}


