#pragma once
#include "jhGameObject.h"

namespace jh
{
	class Animator;
	class Transform;
	class Collider2D;
	class TortoiseMask;

	enum class eTortoiseState
	{
		//Wear Mask
		MaskIdle,
		MaskJump,
		MaskMove, 
		MaskTurn,
		MaskShoot,
		MaskSpawnWing,
		MaskFly,
		MaskFlyShoot,
		RemoveMask,
		RemoveFlyMask,

		//No Mask
		Idle,
		Hit,
		Move,
		EquipMask,
		Fly,
		FlyHit,
		FlyDeath,
		FlyEquipMask,
		Turn,
		Jump,
	};

	class Tortoise
		: public GameObject
	{
	public:
		Tortoise();
		virtual ~Tortoise();

		virtual void Initalize();
		virtual void Update();
		virtual void FixedUpdate();
		virtual void Render();

		//State
		void MaskIdle();
		void MaskJump();
		void MaskMove();
		void MaskTurn();
		void MaskShoot();
		void MaskSpawnWing();
		void MaskFly();
		void MaskFlyShoot();
		void RemoveMask();
		void RemoveFlyMask();

		void Idle();
		void Hit();
		void Move();
		void EquipMask();
		void Fly();
		void FlyHit();
		void FlyDeath();
		void FlyEquipMask();
		void Jump();
		void Turn();

		void FlyBase();
		//Get Set
		eTortoiseState GetPlayerState() { return mTortoiseState; }
		void SetPlayerState(eTortoiseState tortoisestate) { mTortoiseState = tortoisestate; }

		void SetHp(int hp) { mHp = hp; }
		int GetHp() { return mHp; }

		void SetPosition(Vector3 position) { mMonsterPosition = position; }
		Vector3 GetPosition() { return mMonsterPosition; }

		Vector3 GetPlayerRotation() { return mRotation; }
		void SetPlayerRotation(Vector3 rotation) { mRotation = rotation; }

		void SetAniCheck(bool anicheck) { mAniCheck = anicheck; }

		bool GetIsFlying() { return mIsFlying; }

		bool GetMaskOn() { return mMaskOn; }

		float GetIgnoreCollisionTime() { return mIgnoreCollisionTime; }

		bool GetEventOn() { return mEventOn; }

	private:
		Animator* mAnimator;
		Transform* mTransform;
		Collider2D* mCollider;
		eTortoiseState mTortoiseState;
		TortoiseMask* mtortoisemask;

		int mCount;

	private:
		Vector3 mTargetPosition;
		Vector3 mMonsterPosition;
		Vector3 mRotation;

		bool mSpawn;
		bool mAniCheck;
		bool mFunctionCheck;
		bool mTarget;
		bool mStartTrigger;
		bool mIsFlying;
		bool mEventOn;
		int mHp;
		float mElapsedTime;
		bool mMaskOn;
		float mIgnoreCollisionTime;

	};
}

