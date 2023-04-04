#pragma once
#include "jhScript.h"

namespace jh
{

	class Animator;
	class Transform;
	class Rigidbody;

	class PlayerScript
		: public Script
	{
	public:


		PlayerScript();
		~PlayerScript();

		virtual void Initalize() override;
		virtual void Update() override;
		virtual void Render() override;

		virtual void OnCollisionEnter(Collider2D* collider) override;
		virtual void OnCollisionStay(Collider2D* collider) override;
		virtual void OnCollisionExit(Collider2D* collider) override;

		//ePlayerState GetPlayerState() { return mPlayerState; }

		void Start();
		void Action();
		void End();

		//Status
		void Idle();
		void LeftRun();
		void RightRun();
		void Jump();
		void Hurt();
		void Die();

		void StartAttack();
		void Attacking();

		void StartFly();
		void Fly();
		void FlyGrab();
		void FlyCarry();

		//
		void JumpComplete();
	
	private:
		ePlayerState mPlayerState;

		Animator* mAnimator;
		Transform* mTransform;
	
		bool mbCarrying;

		UINT mCount;

		float mTime;
		float mSpeed;

		Vector3 mPlayerPosition;
		bool mbGround;

		Vector2 mVelocity; //�ӵ�
		float mMass; //����
		float mGravity;

	};
}


