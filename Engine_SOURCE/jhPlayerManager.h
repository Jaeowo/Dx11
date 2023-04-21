#pragma once

namespace jh
{
	class Player;
	class Geddy;


	class PlayerManager
	{
	public:
		static void SetPlayer(Player* player) { mPlayer = player; }
		static Player* GetPlayer() { return mPlayer; }

		static void SetGeddy(Geddy* geddy) { mGeddy = geddy; }
		static Geddy* GetGeddy() { return mGeddy; }


	private:
		static Player* mPlayer;
		static Geddy* mGeddy;
		
	};
}


