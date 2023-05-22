#pragma once
#include "jhGameObject.h"



namespace jh
{
	class Transform;
	class Collider2D;
	class PlayerScript;

	class Player
		: public GameObject
	{
	public:
		Player();
		virtual ~Player();

		virtual void Initalize();
		virtual void Update();
		virtual void FixedUpdate();
		virtual void Render();

		ePlayerState GetPlayerState() { return mPlayerState; }
		void SetPlayerState(ePlayerState playerstate) { mPlayerState = playerstate; }

		Vector3 GetPlayerPos() { return mPlayerPos; }
		void SetPlayerPos(Vector3 playerpos) { mPlayerPos = playerpos; }

		bool GetIsGround() { return mbGround; }
		void SetIsGround(bool bGround) { mbGround = bGround; }

		bool GetIsFlyDown() { return mIsFlyingDown; }
		void SetIsFlyDown(bool flyingdown) { mIsFlyingDown = flyingdown; }

		bool GetIsJumping() { return mIsJumping; }
		void SetIsJumping(bool isjumping) { mIsJumping = isjumping; }

		bool GetIsFly() { return mIsFly; }
		void SetIsFly(bool isfly) { mIsFly = isfly; }

		UINT GetCount() { return mCount; }
		void SetCount(UINT count) { mCount = count; }

		Vector3 GetPlayerRotation() { return mRotation; }
		void SetPlayerRotation(Vector3 rotation) { mRotation = rotation; }

		Transform* getTransform() { return mTransform; }

		bool GetIsLeftSlope() { return mIsLeftSlope; }
		bool GetIsRightSlope() { return mIsRightSlope; }
		void SetIsLeftSlope(bool leftslope) { mIsLeftSlope = leftslope; }
		void SetIsRightSlope(bool rightslope) { mIsRightSlope = rightslope; }

		bool GetVelocityZero() { return mvelocityzero; }
		void SetVelocityZero(bool velocityzero) { mvelocityzero = velocityzero; }
	private:
		Transform* mTransform;
		Collider2D* mCollider;

		bool mIsFlyingDown;
		bool mIsFly;
		bool mIsJumping;
		bool mbGround;
		bool mvelocityzero;

		ePlayerState mPlayerState;
		Vector3 mPlayerPos;
		Vector3 mRotation;
		UINT mCount;

		bool mIsLeftSlope;
		bool mIsRightSlope;

		Vector3 mColliderRotation;
	};

}


