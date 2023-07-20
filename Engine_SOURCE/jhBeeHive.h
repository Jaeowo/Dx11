#pragma once
#include "jhGameObject.h"


namespace jh
{
	class Transform;
	class Animator;
	class Phase1;
	class Phase2;
	class Phase3;
	class Phase4;

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

		void p1();
		void p2();
		void p3();
		void p4();
		void Phase5();

		//void SpawnBees(eBeeState beeState);

		void SetPosition(Vector3 position) { mPosition = position; }
		void SetCount(bool onecount) { mOneCount = onecount; }

		void SetDeadBee(int deadbee) { mDeadBees = deadbee; }
		int GetDeadBee() { return mDeadBees; }

		void SetPhaseBee(int phasebee) { mPhaseBeeCount = phasebee; }
		int GetPhaseBee() { return mPhaseBeeCount; }

	private:
		Vector3 mPosition;
		Transform* mTransform;
		Animator* mAnimator;
		eBeeHiveState mBeeHiveState;

		float mSpawnTimer;
		float mPhaseTimer;

		int mDeadBees;

		bool mOneCount;
		bool mPhaseMove;
		float mTotalTime;

		int mPhaseBeeCount;

		Phase1* mphase1;
		Phase2* mphase2;
		Phase3* mphase3;
		Phase4* mphase4;


	};
}
