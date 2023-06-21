#pragma once
#include "jhGameObject.h"

namespace jh
{
	class Animator;
	class Transform;

	class GeddyBullet
		: public GameObject
	{
	public:
		GeddyBullet();
		virtual ~GeddyBullet();

		virtual void Initalize();
		virtual void Update();
		virtual void FixedUpdate();
		virtual void Render();

		bool getIsAttack() { return mIsAttack; }
		void SetIsAttack(bool IsAttack) { IsAttack = mIsAttack; }

		Vector3 GetPosition() { return mPosition; }

	private:
		Animator* mAnimator;
		Transform* mTransform;
		float mSpeed;
		Vector3 mAngle;
		Vector2 mMousePos;
		Vector3 mGeddyPos;
		Vector3 mBulletPos;

		bool mIsDirectionSet;
		Vector2 mDirection;

		Vector3 mPosition;

		float mDeadTime;

		bool mIsAttack;
	};
}


