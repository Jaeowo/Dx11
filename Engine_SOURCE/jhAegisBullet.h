#pragma once
#include "jhGameObject.h"

namespace jh
{
	class Animator;
	class Transform;
	class Tortoise;

	class AegisBullet
		: public GameObject
	{
	public:
		AegisBullet();
		virtual ~AegisBullet();

		virtual void Initalize();
		virtual void Update();
		virtual void FixedUpdate();
		virtual void Render();

		bool getIsAttack() { return mIsAttack; }
		void SetIsAttack(bool IsAttack) { IsAttack = mIsAttack; }

		void SetPosition(const Vector3& position);
		void SetDirection(const Vector3& direction);


	private:
		Animator* mAnimator;
		Transform* mTransform;


		float mSpeed;
		Vector3 mAngle;
		Vector3 mPlayerPos;
		Vector3 mBulletPos;

		bool mIsDirectionSet;
		Vector3 mDirection;

		float mDeadTime;

		bool mIsAttack;
	};
}
