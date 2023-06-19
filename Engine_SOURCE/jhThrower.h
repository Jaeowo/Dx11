#pragma once
#include "jhGameObject.h"

namespace jh
{
	class Transform;
	class Animator;

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

	private:
		Vector3 mPosition;
		Vector3 mTargetPosition;
		Transform* mTransform;
		Animator* mAnimator;
		Vector3 mRotation;
		eThrowerState mThrowerState;

		int mHp;
		bool mOneCount;
		float mTotalTime;
	};
}