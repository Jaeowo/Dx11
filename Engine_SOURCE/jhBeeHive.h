#pragma once
#include "jhGameObject.h"


namespace jh
{
	class Transform;
	class Animator;
	class Bee;

	enum class eBeeHiveState
	{
		Idle,
		Broken,
		Phase1,
		Phase2,
		Phase3,
		Phase4,
		Phase5
	};

	class BeeHive
		: public GameObject
	{
	public:
		BeeHive();
		virtual ~BeeHive();

		virtual void Initalize();
		virtual void Update();
		virtual void FixedUpdate();
		virtual void Render();

		//State
		void Idle();
		void Broken();
		void UpdateBeeCount();

		void Phase1();
		void Phase2();
		void Phase3();
		void Phase4();
		void Phase5();

		void SpawnBees(eBeeState beeState);

		void SetPosition(Vector3 position) { mPosition = position; }
		void SetCount(bool onecount) { mOneCount = onecount; }

		void SetDeadBee(int deadbee) { mDeadBees = deadbee; }
		int GetDeadBee() { return mDeadBees; }

		void SetPhaseBee(int phasebee) { mPhaseBeeCount = phasebee; }
		int GetPhaseBee() { return mPhaseBeeCount; }

		void IncreaseDeadBee() { ++mDeadBees; }
		void DecreaseDeadBee() { --mDeadBees; }
		void IncreasePhaseBee() { ++mPhaseBeeCount; }
		void DecreasePhaseBee() { --mPhaseBeeCount; }

	private:
		Vector3 mPosition;
		Transform* mTransform;
		Animator* mAnimator;
		eBeeHiveState mBeeHiveState;
		Bee* mbee;

		float mSpawnTimer;
		float mPhaseTimer;

		int mDeadBees;

		bool mOneCount;
		bool mPhaseMove;
		float mTotalTime;

		int mPhaseBeeCount;

	};
}
