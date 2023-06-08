#pragma once
#include "jhGameObject.h"

namespace jh
{
	class Animator;
	class Transform;
	class Tortoise;

	class TortoiseBullet
		: public GameObject
	{
	public:
		TortoiseBullet();
		virtual ~TortoiseBullet();

		virtual void Initalize();
		virtual void Update();
		virtual void FixedUpdate();
		virtual void Render();

		bool getIsAttack() { return mIsAttack; }
		void SetIsAttack(bool IsAttack) { IsAttack = mIsAttack; }

		void SetPosition(const Vector3& position);



	private:
		Animator* mAnimator;
		Transform* mTransform;


		float mSpeed;
		Vector3 mAngle;
		Vector3 mPlayerPos;
		Vector3 mBulletPos;

		bool mIsDirectionSet;
		Vector2 mDirection;

		float mDeadTime;

		bool mIsAttack;
	};
}
