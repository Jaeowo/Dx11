#pragma once
#include "jhGameObject.h"

namespace jh
{
	class Transform;
	class Animator;

	enum class eBeeState
	{
		Idle,
		LeftSpawn,
		RightSpawn,
		Attack,
		Follow,
		HitWall,
		Hit,
		Die
	};

	class Bee
		: public GameObject
	{
	public:
		Bee();
		virtual ~Bee();

		virtual void Initalize();
		virtual void Update();
		virtual void FixedUpdate();
		virtual void Render();

		//State
		void Idle();
		void LeftSpawn();
		void RightSpawn();
		void Attack();
		void Follow();
		void HitWall();
		void Hit();
		void Die();

		void SetPosition(Vector3 position) { mPosition = position; }
		void SetCount(bool onecount) { mOneCount = onecount; }

		void SetBeeState(eBeeState beestate) { mBeeState = beestate; }

	private:
		Vector3 mPosition;
		Vector3 mTargetPosition;
		Transform* mTransform;
		Animator* mAnimator;
		Vector3 mRotation;
		eBeeState mBeeState;

		int mHp;
		bool mOneCount;
		float mTotalTime;
	};
}