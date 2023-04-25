#pragma once
#include "jhGameObject.h"

namespace jh
{

	class Transform;
	class Collider2D;


	class Geddy
		: public GameObject
	{
	public:
		Geddy();
		virtual ~Geddy();

		virtual void Initalize();
		virtual void Update();
		virtual void FixedUpdate();
		virtual void Render();

		eGeddyState GetGeddyState() { return mGeddyState; }
		void SetGeddyState(eGeddyState geddystate) { mGeddyState = geddystate; }

		Vector3 GetPlayerPos() { return mPlayerPos; }
		void SetPlayerPos(Vector3 playerpos) { mPlayerPos = playerpos; }

		bool GetIsGround() { return mbGround; }
		void SetIsGround(bool bGround) { mbGround = bGround; }

		Transform* getTransform() { return mTransform; }

		int GetCount() { return mCount; }
		void SetCount(int Count) { mCount = Count; }

	private:
		Transform* mTransform;
		Transform* mPlayerTransform;
		Collider2D* mCollider;


		eGeddyState mGeddyState;
		Vector3 mPlayerPos;
		bool mbGround;
		int mCount;

	};
}


