#include "jhGrassScript.h"
#include "jhTransform.h"
#include "jhPlayer.h"
#include "jhPlayerManager.h"

namespace jh
{
	GrassScript::GrassScript()
		:Script()
		, mParallax(1.03f)
	{
	}
	GrassScript::~GrassScript()
	{
	}
	void GrassScript::Initalize()
	{
	}
	void GrassScript::Update()
	{

		Transform* tr = GetOwner()->GetComponent<Transform>();

		Vector3 playerPosition = jh::PlayerManager::GetPlayer()->GetPlayerPos();

		Vector3 backSkyPosition = Vector3((playerPosition.x * mParallax + 0.2f), (playerPosition.y * mParallax + 0.5f), 1.7f);

		tr->SetPosition(backSkyPosition);

	}
	void GrassScript::Render()
	{
	}
	void GrassScript::OnCollisionEnter(Collider2D* collider)
	{
	}
	void GrassScript::OnCollisionStay(Collider2D* collider)
	{
	}
	void GrassScript::OnCollisionExit(Collider2D* collider)
	{
	}
}