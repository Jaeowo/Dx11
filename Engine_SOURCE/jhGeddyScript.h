#pragma once
#include "jhScript.h"


namespace jh
{
	class Animator;
	class Transform;
	class Geddyhands;
	class GeddyBullet;

	class GeddyScript
		: public Script
	{
	public:

		GeddyScript();
		~GeddyScript();

		virtual void Initalize() override;
		virtual void Update() override;
		virtual void Render() override;

		virtual void OnCollisionEnter(Collider2D* collider) override;
		virtual void OnCollisionStay(Collider2D* collider) override;
		virtual void OnCollisionExit(Collider2D* collider) override;

		//status
		void Idle();
		void Hanging();
		void Falling();


	private:
		Animator* mAnimator;
		Transform* mTransform;
		Transform* mPlayerTransform;
		Geddyhands* mGeddyhands;
		GeddyBullet* mGeddyBullet;

		eGeddyState mGeddyState;
		int mCount;
		Vector3 mGeddyPosition;
		Vector3 mBeforePos;

		float mFallingTime;
		bool mbGround;

		Vector2 mVelocity;
		float mMass;
		float mGravity;
	};
}


