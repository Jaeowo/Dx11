#include "jhMovingHandScript.h"
#include "jhInput.h"
#include "jhAnimator.h"
#include "jhTransform.h"
#include "jhResources.h"
#include "jhGameObject.h"
#include "jhTime.h"

namespace jh
{
	MovingHandScript::MovingHandScript()
	{
		//Animator* mAnimator = GetOwner()->GetComponent<Animator>();
		//Transform* mTransform = GetOwner()->GetComponent<Transform>();

		//std::shared_ptr<Texture> geddyhandstexture = Resources::Load<Texture>(L"GeddyArm", L"Geddy\\arm_48x32.png");
		//mAnimator->Create(L"Stop", geddyhandstexture, Vector2(0.0f, 0.0f), Vector2(48.0f, 32.0f), Vector2::Zero, 1, 0.25f);
		//mAnimator->Create(L"Shoot1", geddyhandstexture, Vector2(0.0f, 0.0f), Vector2(48.0f, 32.0f), Vector2::Zero, 5, 0.25f);
		//mAnimator->Create(L"Shoot2", geddyhandstexture, Vector2(48.0f, 32.0f), Vector2(48.0f, 32.0f), Vector2::Zero, 5, 0.25f);

		//mAnimator->Play(L"Stop", true);

		//mAngle = mTransform->GetRotation();
	}
	MovingHandScript::~MovingHandScript()
	{
	}
	void MovingHandScript::Initalize()
	{
	}
	void MovingHandScript::Update()
	{
	/*	mTransform = GetOwner()->GetComponent<Transform>();
		mAnimator = GetOwner()->GetComponent<Animator>();

		if (Input::GetKey(eKeyCode::F))
		{
			mAngle.z += 50.0f * Time::DeltaTime();
			mTransform->SetRotation(mAngle);
		}*/

	}
	void MovingHandScript::Render()
	{
	}
	void MovingHandScript::OnCollisionEnter(Collider2D* collider)
	{
	}
	void MovingHandScript::OnCollisionStay(Collider2D* collider)
	{
	}
	void MovingHandScript::OnCollisionExit(Collider2D* collider)
	{
	}
}