#include "jhPlayerManager.h"
#include "jhPlayer.h"

namespace jh
{
	Player* PlayerManager::mPlayer = nullptr;
	Geddy* PlayerManager::mGeddy = nullptr;
    int PlayerManager::mSavedHp = 0;
    int PlayerManager::mSavedCoins = 0;

    void PlayerManager::SavePlayerState(Player* player)
    {
        mSavedHp = player->GetHp();
        mSavedCoins = player->GetCoin();
    }

    void PlayerManager::LoadPlayerState(Player* player) 
    {
        player->SetHp(mSavedHp);
        player->SetCoin(mSavedCoins);
    }
}