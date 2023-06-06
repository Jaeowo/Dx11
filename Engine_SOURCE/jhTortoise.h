#pragma once
#include "jhGameObject.h"

namespace jh
{
	class Animator;
	class Transform;

	enum class eTortoiseState
	{
		//Wear Mask
		MaskIdle,
		MaskJump,
		MaskMove, //Rotation값 이용해서 left,right방향 감지하기
		MaskTurn,
		MaskShoot,
		MaskSpawnWing,
		MaskFly,
		MaskFlyShoot,

		//No Mask
		Idle,
		Hit,
		Move,
		EquipMask,
		Fly,
		FlyHit,
		FlyDeath,
		FlyEquipMask,
		FindMask,
		Turn,
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

		void Idle();
		void Hit();
		void Move();
		void EquipMask();
		void Fly();
		void FlyHit();
		void FlyDeath();
		void FlyEquipMask();
		void FindMask();
		void Turn();

		//Get Set
		eTortoiseState GetPlayerState() { return mTortoiseState; }
		void SetPlayerState(eTortoiseState tortoisestate) { mTortoiseState = tortoisestate; }

		void SetHp(int hp) { mHp = hp; }

		void SetPosition(Vector3 position) { mMonsterPosition = position; }
		Vector3 GetPosition() { return mMonsterPosition; }

	private:
		Animator* mAnimator;
		Transform* mTransform;
		eTortoiseState mTortoiseState;

		int mCount;

	private:
		Vector3 mTargetPosition;
		Vector3 mMonsterPosition;
		bool mCheck;
		bool mTarget;
		int mHp;
		float mElapsedTime;
	};
}

