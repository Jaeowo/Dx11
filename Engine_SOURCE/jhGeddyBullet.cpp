#include "jhGeddyBullet.h"
#include "jhAnimator.h"
#include "jhTransform.h"
#include "jhResources.h"
#include "jhInput.h"
#include "jhApplication.h"
#include "jhCamera.h"
#include "jhPlayerManager.h"
#include "jhGeddy.h"
#include "jhSpriteRenderer.h"
#include "jhRenderer.h"
extern jh::Application application;

namespace jh
{
	GeddyBullet::GeddyBullet()
		: mSpeed(1.0f)
		, mIsAttack(false) 
	{
	/*	Animator* mAnimator = AddComponent<Animator>();
		


		
		mTransform->SetScale(Vector3(0.29f, 0.29f, 1.0f));*/

		/*
		BulletScript 따로 만들어서 충돌시 IsAttack true로 바꿔주고
		delete되도록
		프리팹 생기면 총알 넣자 !!!!
		*/
		Animator* mAnimator = AddComponent<Animator>();

		mTransform = GetComponent<Transform>();
		

		std::shared_ptr<Texture> mechanicbullettexture = Resources::Load<Texture>(L"MechanicBullet", L"Bullets\\sprMechanicBullet_38x31.png");
		mAnimator->Create(L"Shooting", mechanicbullettexture, Vector2(0.0f, 0.0f), Vector2(38.0f, 31.0f), Vector2::Zero, 1, 0.3f);
		mAnimator->Create(L"Attack", mechanicbullettexture, Vector2(0.0f, 0.0f), Vector2(38.0f, 31.0f), Vector2::Zero, 5, 0.3f);
	
		mAnimator->Play(L"Shooting", true);

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

		mGeddyPos = PlayerManager::GetGeddy()->GetPos();
		mTransform->SetPosition(mGeddyPos);
		mBulletPos = mTransform->GetPosition();

		mMousePos = Input::GetMousePosition();
		float mouseX = (2.0f * mMousePos.x) / application.GetWidth() - 1.0f;
		float mouseY = 1.0f - (2.0f * mMousePos.y) / application.GetHeight();
		Vector4 ndcPos = Vector4(mouseX, mouseY, 0.0f, 1.0f);
		Matrix viewMatrix = Camera::GetGpuViewMatrix();
		Matrix inverseViewMatrix = viewMatrix.Invert();
		Vector4 viewPos = Vector4::Transform(ndcPos, inverseViewMatrix);
		mMousePos = Vector2(viewPos.x, viewPos.y);

		Vector2 direction = mMousePos - mBulletPos;
		direction.Normalize();

		Vector2 velocity = direction * mSpeed;
		

		/*
		Vector3 Dir = mTargetPosition - mMonsterPosition;
		Dir.Normalize();

		mMonsterPosition += (mTargetPosition * Dir) * (Time::DeltaTime() /10.0f) ;
		*/
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