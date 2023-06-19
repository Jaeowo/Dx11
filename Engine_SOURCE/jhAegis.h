#pragma once
#include "jhGameObject.h"

namespace jh
{
	class Transform;
	class Animator;

	enum class eAegisState
	{
		Idle,
		WaitShoot,
		Shoot,
		Die
	};

	class Aegis
		: public GameObject
	{
	public:
		Aegis();
		virtual ~Aegis();

		virtual void Initalize();
		virtual void Update();
		virtual void FixedUpdate();
		virtual void Render();

		//State
		void Idle();
		void WaitShoot();
		void Shoot();
		void Die();

		void SetPosition(Vector3 position) { mPosition = position; }
		void SetCount(bool onecount) { mOneCount = onecount; }

		void SetAegisState(eAegisState aegisstate) { mAegisState = aegisstate; }

	private:
		Vector3 mPosition;
		Vector3 mTargetPosition;
		Transform* mTransform;
		Animator* mAnimator;
		Vector3 mRotation;
		eAegisState mAegisState;
		
		float mMinY;
		float mMaxY;

		int mHp;
		bool mOneCount;
		float mTotalTime;
	};
}