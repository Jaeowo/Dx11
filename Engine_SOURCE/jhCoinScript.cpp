#include "jhCoinScript.h"
#include "jhCoin.h"
#include "jhPlayer.h"
#include "jhTime.h"

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
		/*	if (playerObj->GetPlayerState() != ePlayerState::FlyGrab)
			{
				int coinCheck = 0;
				coinCheck = (playerObj->GetCoin() + 1);
				playerObj->SetCoin(coinCheck);

				mcoin->Death();
			}*/
			if (mCount == 0)
			{
				mTime = 0.0f;
				mCount = 1;
			}
		
			if (mTime >= 1.0f)
			{
	/*			int coinCheck = 0;
				coinCheck = (playerObj->GetCoin() + 1);
				playerObj->SetCoin(coinCheck);

				mcoin->Death();*/
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