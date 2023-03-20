#pragma once
#include "jhGameObject.h"

class PlayerScript;

namespace jh
{
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

	private:
		friend class PlayerScript;
		ePlayerState mPlayerState;
	};
}


