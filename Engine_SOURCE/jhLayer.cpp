#include "jhLayer.h"


namespace jh
{
	Layer::Layer()
	{
	}

	Layer::~Layer()
	{
		for (GameObject* obj : mGameObjects)
		{
			if (obj == nullptr)
				continue;

			delete obj;
			obj = nullptr;
		}
	}

	void Layer::Initalize()
	{
		for (GameObject* obj : mGameObjects)
		{
			if (obj == nullptr)
				continue;

			obj->Initalize();
		}
	}

	void Layer::Update()
	{
		for (GameObject* obj : mGameObjects)
		{
			if (obj == nullptr)
				continue;
			if (obj->GetState() != GameObject::eState::Active)
				continue;

			obj->Update();
		}
	}

	void Layer::FixedUpdate()
	{
		for (GameObject* obj : mGameObjects)
		{
			if (obj == nullptr)
				continue;

			obj->FixedUpdate();
		}
	}

	void Layer::Render()
	{
		for (GameObject* obj : mGameObjects)
		{
			if (obj == nullptr)
				continue;
			if (obj->GetState() != GameObject::eState::Active)
				continue;


			obj->Render();
		}
	}

	void Layer::AddGameObject(GameObject* gameObject)
	{
		if (gameObject == nullptr)
			return;

		mGameObjects.push_back(gameObject);
	}
	std::vector<GameObject*> Layer::GetDontDestroyGameObjects()
	{
		std::vector<GameObject*> donts;
		for (GameObjectIter iter = mGameObjects.begin()
			; iter != mGameObjects.end()
			; )
		{
			if ((*iter)->IsDontDestroy() == true)
			{
				donts.push_back((*iter));
				mGameObjects.erase(iter);
			}
			else
			{
				iter++;
			}
		}

		return donts;
	}
}