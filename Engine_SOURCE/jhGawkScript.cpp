#include "jhGawkScript.h"
#include "jhGawk.h"
#include "jhPlayer.h"
#include "jhGeddyBullet.h"

namespace jh
{
	GawkScript::GawkScript()
		:Script()
	{

	}
	GawkScript::~GawkScript()
	{
	}
	void GawkScript::Initalize()
	{
		mgawk = dynamic_cast<Gawk*>(GetOwner());
	}
	void GawkScript::Update()
	{

	}
	void GawkScript::Render()
	{
	}
	void GawkScript::OnCollisionEnter(Collider2D* collider)
	{
		Player* playerObj = dynamic_cast<Player*>(collider->GetOwner());

		if (playerObj)
		{

		}

		GeddyBullet* geddyBulletObj = dynamic_cast<GeddyBullet*>(collider->GetOwner());
		if (geddyBulletObj)
		{
			mgawk->SetCount(0);
			mgawk->SetState(eGawkState::Hurt);
		}
		
	}
	void GawkScript::OnCollisionStay(Collider2D* collider)
	{
	}
	void GawkScript::OnCollisionExit(Collider2D* collider)
	{
	}
}