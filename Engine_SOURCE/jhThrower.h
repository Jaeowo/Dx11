#pragma once
#include "jhGameObject.h"

namespace jh
{
	class Transform;
	class Animator;
	class Collider2D;

	enum class eThrowerState
	{
		Idle,
		Follow,
		ThrowWait,
		Throw,
		Hurt
	};

	class Thrower
		: public GameObject
	{
	public:
		Thrower();
		virtual ~Thrower();

		virtual void Initalize();
		virtual void Update();
		virtual void FixedUpdate();
		virtual void Render();

		//State
		void Idle();
		void Follow();
		void ThrowWait();
		void Throw();
		void Hurt();

		void SetPosition(Vector3 position) { mPosition = position; }
		void SetCount(bool onecount) { mOneCount = onecount; }

		eThrowerState GetThrowerState() { return mThrowerState; }
		void SetThrowerState(eThrowerState throwerstate) { mThrowerState = throwerstate; }
 
		Vector3 GetPreviousPos() { return mPrevPosition; }
	private:
		Vector3 mPosition;
		Vector3 mTargetPosition;
		Vector3 mPrevPosition;
		Transform* mTransform;
		Animator* mAnimator;
		Collider2D* mCollider;

		Vector3 mRotation;
		eThrowerState mThrowerState;

		int mHp;
		bool mOneCount;
		float mTotalTime;

	};
}