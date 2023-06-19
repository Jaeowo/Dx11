#pragma once
#include "jhGameObject.h"

namespace jh
{
	class StoneDoor;

	class MonsterSpawn
		: public GameObject
	{
	public:
		MonsterSpawn();
		virtual ~MonsterSpawn();

		virtual void Initalize();
		virtual void Update();
		virtual void FixedUpdate();
		virtual void Render();

		void SetCount(bool onecount) { mOneCount = onecount; }

	private:
		bool mOneCount;
		float mTotalTime;
		StoneDoor* mStoneDoor;
		std::vector<GameObject*> mMonsters;
	};
}