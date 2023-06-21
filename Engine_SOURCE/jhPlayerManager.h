#pragma once

namespace jh
{
	class Player;
	class Geddy;
	class BeeHive;

	class PlayerManager
	{
	public:
		static void SetPlayer(Player* player) { mPlayer = player; }
		static Player* GetPlayer() { return mPlayer; }

		static void SetGeddy(Geddy* geddy) { mGeddy = geddy; }
		static Geddy* GetGeddy() { return mGeddy; }

		static void SetBeeHive(BeeHive* beehive) { mBeeHive = beehive; }
		static BeeHive* GetBeeHive() { return mBeeHive; }

		static void SavePlayerState(Player* player);
		static void LoadPlayerState(Player* player);

	private:
		static Player* mPlayer;
		static Geddy* mGeddy;
		static BeeHive* mBeeHive;

		static int mSavedHp;
		static int mSavedCoins;
		
	};
	int PlayerManager::mSavedHp = 0;
	int PlayerManager::mSavedCoins = 0;
}


