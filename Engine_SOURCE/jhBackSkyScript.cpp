#include "jhBackSkyScript.h"
#include "jhTransform.h"
#include "jhPlayer.h"
#include "jhPlayerManager.h"

namespace jh
{
	BackSkyScript::BackSkyScript()
		:Script()
		, mParallax(0.95f)
	{
	}
	BackSkyScript::~BackSkyScript()
	{
	}
	void BackSkyScript::Initalize()
	{
	}
	void BackSkyScript::Update()
	{
	

		Transform* tr = GetOwner()->GetComponent<Transform>();

		Vector3 playerPosition = jh::PlayerManager::GetPlayer()->GetPlayerPos();

		Vector3 backSkyPosition = Vector3((playerPosition.x * mParallax + 0.2f), (playerPosition.y * mParallax +0.5f), 1.7f);

		tr->SetPosition(backSkyPosition);

	}
	void BackSkyScript::Render()
	{
	}
	void BackSkyScript::OnCollisionEnter(Collider2D* collider)
	{
	}
	void BackSkyScript::OnCollisionStay(Collider2D* collider)
	{
	}
	void BackSkyScript::OnCollisionExit(Collider2D* collider)
	{
	}
}