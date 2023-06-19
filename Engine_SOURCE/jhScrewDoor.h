#pragma once
#include "jhGameObject.h"

namespace jh
{
	class StoneDoor;
	class ScrewPuzzle;

	class ScrewDoor
		: public GameObject
	{
	public:
		ScrewDoor();
		virtual ~ScrewDoor();

		virtual void Initalize();
		virtual void Update();
		virtual void FixedUpdate();
		virtual void Render();

		void SetCount(bool onecount) { mOneCount = onecount; }

	private:
		bool mOneCount;
		float mTotalTime;
		StoneDoor* mStoneDoor;
		ScrewPuzzle* mScrewPuzzle1;
		ScrewPuzzle* mScrewPuzzle2;
		ScrewPuzzle* mScrewPuzzle3;
		std::vector<GameObject*> mMonsters;
	};
}