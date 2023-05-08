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

		bool GetIsFly() { return mIsFly; }
		void SetIsFly(bool isfly) { mIsFly = isfly; }

		UINT GetCount() { return mCount; }
		void SetCount(UINT count) { mCount = count; }

		Vector3 GetPlayerRotation() { return mRotation; }
		void SetPlayerRotation(Vector3 rotation) { mRotation = rotation; }

		Transform* getTransform() { return mTransform; }

		void SetIsLeftSlope(bool leftslope) { mIsLeftSlope = leftslope; }
		void SetIsRightSlope(bool rightslope) { mIsRightSlope = rightslope; }

	private:
		Transform* mTransform;
		Collider2D* mCollider;

		bool mIsFlyingDown;
		bool mIsFly;
		bool mbGround;
		bool mIsSlope;

		ePlayerState mPlayerState;
		Vector3 mPlayerPos;
		Vector3 mRotation;
		UINT mCount;

		bool mIsLeftSlope;
		bool mIsRightSlope;

		Vector3 mColliderRotation;
	};

}


