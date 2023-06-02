#pragma once
#include "jhGameObject.h"

namespace jh
{
	class Animator;
	class Transform;

	enum class eTortoiseState
	{
		Idle,
		Jump,
		Move, //BlinkEye, Nomask
		MoveShoot,
		EquipMask,
		TurnMask,

		SpawnWings,
		Fly, //Nomask,Mask 값 나누기
		FlyEquipMask,
		FlyDeath,

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
		void Idle();
		void Jump();
		void Move();
		void MoveShoot();
		void EquipMask();
		void TurnMask();

		void SpawnWings();
		void Fly();
		void FlyEquipMask();
		void FlyDeath();

		//Get Set
		eTortoiseState GetPlayerState() { return mTortoiseState; }
		void SetPlayerState(eTortoiseState tortoisestate) { mTortoiseState = tortoisestate; }

		void SetHp(int hp) { mHp = hp; }

	private:
		Animator* mAnimator;
		Transform* mTransform;
		eTortoiseState mTortoiseState;

		int mCount;

	private:
		Vector3 mTargetPosition;
		Vector3 mMonsterPosition;
		bool mTarget;
		int mHp;
		float mElapsedTime;
	};
}

