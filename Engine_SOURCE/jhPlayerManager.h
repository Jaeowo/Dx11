#pragma once

namespace jh
{
	class Player;

	class PlayerManager
	{
	public:
		static void SetPlayer(Player* player) { mPlayer = player; }
		static Player* GetPlayer() { return mPlayer; }

	private:
		static Player* mPlayer;

	};
}


