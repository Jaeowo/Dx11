#include "jhCloudScript.h"
#include "jhTransform.h"
#include "jhGameObject.h"
#include "jhInput.h"
#include "jhTime.h"
#include "jhPlayer.h"
#include "jhTransform.h"

namespace jh
{
	CloudScript::CloudScript()
		:Script()
	{
		
	}
	CloudScript::~CloudScript()
	{
	}
	void CloudScript::Initalize()
	{
	}
	void CloudScript::Update()
	{
		Transform* tr = GetOwner()->GetComponent<Transform>();
		Vector3 pos = tr->GetPosition();
		pos.x -= 0.015f * Time::DeltaTime();
		tr->SetPosition(pos);

		//Transform* tr
		//Vector3 TargetPos = PlayerManager::GetPlayer()->GetPlayerPos();
		
		
	}
	void CloudScript::Render()
	{
	}
	void CloudScript::OnCollisionEnter(Collider2D* collider)
	{

	}
	void CloudScript::OnCollisionStay(Collider2D* collider)
	{
	}
	void CloudScript::OnCollisionExit(Collider2D* collider)
	{
	}
}