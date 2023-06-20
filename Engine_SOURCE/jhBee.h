#pragma once
#include "jhGameObject.h"

namespace jh
{
	class Transform;
	class Animator;

	enum class eBeeState
	{
		Idle,
		Attack,
		Follow,
		HitWall,
		Hit,
		Death,
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
		void Attack();
		void Follow();
		void HitWall();
		void Hit();
		void BeeDeath();

		void SetPosition(Vector3 position) { mPosition = position; }
		void SetCount(bool onecount) { mOneCount = onecount; }

	private:
		Vector3 mPosition;
		Transform* mTransform;
		Animator* mAnimator;
		eBeeState mBeeState;

		bool mOneCount;
		float mTotalTime;
		int mHp;

		Vector3 mMoveDirection;
		float mMoveSpeed;
		float mWobbleMagnitude;
		float mWobbleSpeed;
		Vector3 mPlayerPosition;
	};
}