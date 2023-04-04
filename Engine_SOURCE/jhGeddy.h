#pragma once
#include "jhGameObject.h"

namespace jh
{
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

		eGeddyState GetPlayerState() { return mGeddyState; }
		void SetPlayerState(eGeddyState geddystate) { mGeddyState = geddystate; }

		Vector3 GetPlayerPos() { return mPlayerPos; }
		void SetPlayerPos(Vector3 playerpos) { mPlayerPos = playerpos; }

		bool GetIsGround() { return mbGround; }
		void SetIsGround(bool bGround) { mbGround = bGround; }

	private:
		eGeddyState mGeddyState;
		Vector3 mPlayerPos;
		bool mbGround;
	};
}


