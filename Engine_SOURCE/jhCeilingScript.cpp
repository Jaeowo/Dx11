#include "jhCeilingScript.h"
#include "jhTransform.h"
#include "jhPlayer.h"
#include "jhPlayerManager.h"

namespace jh
{
	CeilingScript::CeilingScript()
		:Script()
		, mParallax(1.03f)
	{
	}
	CeilingScript::~CeilingScript()
	{
	}
	void CeilingScript::Initalize()
	{
	}
	void CeilingScript::Update()
	{

		Transform* tr = GetOwner()->GetComponent<Transform>();

		Vector3 playerPosition = jh::PlayerManager::GetPlayer()->GetPlayerPos();

		Vector3 backSkyPosition = Vector3((playerPosition.x * mParallax + 0.2f), (playerPosition.y * mParallax + 0.5f), 1.7f);

		tr->SetPosition(backSkyPosition);

	}
	void CeilingScript::Render()
	{
	}
	void CeilingScript::OnCollisionEnter(Collider2D* collider)
	{
	}
	void CeilingScript::OnCollisionStay(Collider2D* collider)
	{
	}
	void CeilingScript::OnCollisionExit(Collider2D* collider)
	{
	}
}