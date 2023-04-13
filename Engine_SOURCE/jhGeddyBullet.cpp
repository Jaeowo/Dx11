#include "jhGeddyBullet.h"
#include "jhAnimator.h"
#include "jhTransform.h"
#include "jhResources.h"

namespace jh
{
	GeddyBullet::GeddyBullet()
	{
		Animator* mAnimator = AddComponent<Animator>();
		mTransform = GetComponent<Transform>();

		std::shared_ptr<Texture> mechanicbullettexture = Resources::Load<Texture>(L"MechanicBullet", L"Bullets\\sprMechanicBullet_38x31.png");
		mAnimator->Create(L"Shooting", mechanicbullettexture, Vector2(0.0f, 0.0f), Vector2(38.0f, 31.0f), Vector2::Zero, 5, 0.1f);

		mAnimator->Play(L"Shooting", false);
	}
	GeddyBullet::~GeddyBullet()
	{
	}
	void GeddyBullet::Initalize()
	{
		GameObject::Initalize();

	}
	void GeddyBullet::Update()
	{
		GameObject::Update();

	}
	void GeddyBullet::FixedUpdate()
	{
		GameObject::FixedUpdate();
	}
	void GeddyBullet::Render()
	{
		GameObject::Render();
	}
}