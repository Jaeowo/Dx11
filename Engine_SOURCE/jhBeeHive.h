#pragma once
#include "jhGameObject.h"

namespace jh
{
	class Transform;
	class Animator;

	enum class eBeeHiveState
	{
		Idle,
		SpawnBees,
		Broken
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
		void SpawnBees();
		void Broken();

		void SetPosition(Vector3 position) { mPosition = position; }
		void SetCount(bool onecount) { mOneCount = onecount; }

	private:
		Vector3 mPosition;
		Transform* mTransform;
		Animator* mAnimator;
		eBeeHiveState mBeeHiveState;

		float mSpawnTimer;
		int mSpawnedBees;
		int mDeadBees;
		int mSpawnCycle;

		bool mOneCount;
		float mTotalTime;
	};
}