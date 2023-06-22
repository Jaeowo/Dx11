#include "jhCoinScript.h"
#include "jhCoin.h"
#include "jhPlayer.h"
#include "jhTime.h"
#include "jhAudioClip.h"
#include "jhAudioSource.h"
#include "jhResources.h"

namespace jh
{
	CoinScript::CoinScript()
		:Script()
		,mCount(0)
	{

	}
	CoinScript::~CoinScript()
	{
	}
	void CoinScript::Initalize()
	{
		mcoin = dynamic_cast<Coin*>(GetOwner());
	}
	void CoinScript::Update()
	{
		mTime += Time::DeltaTime();
	}
	void CoinScript::Render()
	{
	}
	void CoinScript::OnCollisionEnter(Collider2D* collider)
	{
		Player* playerObj = dynamic_cast<Player*>(collider->GetOwner());
	
		if (playerObj)
		{
			if (mCount == 0)
			{
				mTime = 0.0f;
				mCount = 1;
			}
		
			if (mTime >= 1.0f)
			{
				int coinCheck = (playerObj->GetCoin() + 5);
				playerObj->SetCoin(coinCheck);
				mcoin->SetSoundOn(true);

				//mcoin->Death();
			}
		}
	
	}
	void CoinScript::OnCollisionStay(Collider2D* collider)
	{
	}
	void CoinScript::OnCollisionExit(Collider2D* collider)
	{
	}
}