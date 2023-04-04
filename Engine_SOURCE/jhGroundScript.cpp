#include "jhGroundScript.h"
#include "jhCollider2D.h"
#include "jhPlayer.h"
#include "jhPlayerManager.h"

namespace jh
{
	GroundScript::GroundScript()
	{
	}
	GroundScript::~GroundScript()
	{
	}
	void GroundScript::Initalize()
	{
	}
	void GroundScript::Update()
	{
	}
	void GroundScript::Render()
	{
	}
	void GroundScript::OnCollisionEnter(Collider2D* collider)
	{
		Player* playerObj = dynamic_cast<Player*>(collider->GetOwner());

		playerObj->SetIsGround(true);
	
	
	}
	void GroundScript::OnCollisionStay(Collider2D* collider)
	{
	}
	void GroundScript::OnCollisionExit(Collider2D* collider)
	{
	}
}