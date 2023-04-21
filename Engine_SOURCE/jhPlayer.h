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

		UINT GetCount() { return mCount; }
		void SetCount(UINT count) { mCount = count; }

	private:
		Transform* mTransform;
		Collider2D* mCollider;
		PlayerScript* mPlayerScript;

		ePlayerState mPlayerState;
		Vector3 mPlayerPos;
		bool mbGround;
		UINT mCount;
	};

}


