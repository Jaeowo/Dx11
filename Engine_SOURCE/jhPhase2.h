#pragma once
#include "jhGameObject.h"

namespace jh
{

	class Phase2
		: public GameObject
	{
	public:
		Phase2();
		virtual ~Phase2();

		virtual void Initalize();
		virtual void Update();
		virtual void FixedUpdate();
		virtual void Render();

		void SetCount(bool onecount) { mOneCount = onecount; }
		bool GetClear() { return mClear; }

	private:
		bool mOneCount;

		bool mClear;
		float mTotalTime;
		float mSpawnTime;
		int mSpawnCount;



		std::vector<GameObject*> mMonsters;
	};
}