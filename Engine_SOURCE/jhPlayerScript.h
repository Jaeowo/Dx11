#pragma once
#include "jhScript.h"

namespace jh
{

	class Animator;
	class Transform;
	class Player;
	class Collider2D;
	class PlayerAttackCol;
	class AudioSource;

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

		void Start();
		void Action();
		void End();


		Vector3 GetPlayerPos() { return mPlayerPosition; }
		void SetPlayerPos(Vector3 playerpos) { mPlayerPosition = playerpos; }

		//Status
		void Idle();
		void LeftRun();
		void RightRun();
		void Jump();
		void Fall();
		void Hurt();
		void Die();
		void GroundRoll();
		void EnterDoor();

		void StartAttack();
		void Attacking();

		void StartFly();
		void Fly();
		void FlyGrab();
		void FlyCarry();
		void FlyAttack();
		void FlyHurt();
		void StartFlyRoll();
		void FlyRoll();
		
		void EventOn();
	
		void JumpComplete();
	
	private:

		ePlayerState mPlayerState;
		ePlayerState mPrevState;

		Animator* mAnimator;
		Transform* mTransform;
		Player* mPlayer;
		PlayerAttackCol* mAttackCol;
	
		bool mbCarrying;

		UINT mCount;

		float mFallingTime;
		float mTime;
		float mSpeed;

		Vector3 mPrevPosition;
		Vector3 mPlayerPosition;
		Vector3 mNewPosition;
		bool mbGround;
		bool mIsFlying; //Flying상태일때 중력 안받도록 예외처리 하기
		bool mHurtCheck;

		Vector3 mRotation;
		Vector2 mVelocity; //속도
		float mMass; //질량
		float mGravity;

		int mHp;
		int mCoin;

		AudioSource* maudioSource;
	

	};
}


