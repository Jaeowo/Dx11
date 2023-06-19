#include "jhMonsterSpawn.h"
#include "jhThrower.h"
#include "jhAegis.h"
#include "jhObject.h"
#include "jhStoneDoor.h"

namespace jh
{
	MonsterSpawn::MonsterSpawn()
		: mOneCount(false)
	{
		//Thrower
		Thrower* throwerObj = object::Instantiate<Thrower>(eLayerType::Monster);
		throwerObj->SetPosition(Vector3(-0.5f, -1.64f, 1.7f));
		mMonsters.push_back(throwerObj);

		//Aegis
		Aegis* aegisObj = object::Instantiate<Aegis>(eLayerType::Monster);
		aegisObj->SetPosition(Vector3(-0.54f, 0.45f, 1.7f));
		mMonsters.push_back(aegisObj);

		Aegis* aegisObj2 = object::Instantiate<Aegis>(eLayerType::Monster);
		aegisObj2->SetPosition(Vector3(-0.33f, 0.45f, 1.7f));
		mMonsters.push_back(aegisObj2);

		mStoneDoor = object::Instantiate<StoneDoor>(eLayerType::BackGround);
		mStoneDoor->SetPosition(Vector3(0.8f, 0.3f, 1.7f));
		mStoneDoor->SetScale(Vector3(0.45f, 0.47f, 1.0f));
		mStoneDoor->SetRotation(Vector3(0.0f, 0.0f, 270.0f));
		mStoneDoor->SetCenter(Vector2(0.0f, -0.04f));


	}
	MonsterSpawn::~MonsterSpawn()
	{
	}
	void MonsterSpawn::Initalize()
	{
		GameObject::Initalize();
	}
	void MonsterSpawn::Update()
	{
		GameObject::Update();

		for (auto it = mMonsters.begin(); it != mMonsters.end(); )
		{
			if ((*it)->IsDead())
			{
				it = mMonsters.erase(it);
			}
			else
			{
				++it;
			}
		}

		if (mMonsters.empty())
		{
			if (mOneCount == false)
			{
				mStoneDoor->SetOpenTrigger(true);
				mStoneDoor->SetCount(false);
				mOneCount = true;
			}
		}
	}
	void MonsterSpawn::FixedUpdate()
	{
		GameObject::FixedUpdate();
	}
	void MonsterSpawn::Render()
	{
		GameObject::Render();
	}

}