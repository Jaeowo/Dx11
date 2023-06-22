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
#include "jhPlayer.h"
#include "jhTime.h"
#include "jhCollider2D.h"
#include "jhAudioClip.h"
#include "jhAudioSource.h"
#include "jhGeddyBulletEffect.h"
#include "jhObject.h"

extern jh::Application application;

namespace jh
{
	GeddyBullet::GeddyBullet()
		: mSpeed(0.8f)
		, mIsAttack(false) 
		, mIsDirectionSet(false)
		, mDeadTime(0.0f)
	{

		mAnimator = AddComponent<Animator>();
		mTransform = GetComponent<Transform>();

		std::shared_ptr<Texture> mechanicbullettexture = Resources::Load<Texture>(L"MechanicBullet", L"Bullets\\sprMechanicBullet_38x31.png");
		mAnimator->Create(L"Shooting", mechanicbullettexture, Vector2(0.0f, 0.0f), Vector2(38.0f, 31.0f), Vector2::Zero, 1, 0.3f);
		mAnimator->Create(L"Attack", mechanicbullettexture, Vector2(0.0f, 0.0f), Vector2(38.0f, 31.0f), Vector2::Zero, 5, 0.3f);
	
		mAnimator->Play(L"Shooting", true);

		SpriteRenderer* geddyhandssr = AddComponent<SpriteRenderer>();
		std::shared_ptr<Mesh> geddyhandsmesh = Resources::Find<Mesh>(L"RectMesh");
		std::shared_ptr<Material> geddyhandsmaterial = Resources::Find<Material>(L"Mechanicbulletmaterial");
		geddyhandssr->SetMaterial(geddyhandsmaterial);
		geddyhandssr->SetMesh(geddyhandsmesh);


		mTransform->SetPosition(Vector3(0.887f, 0.823f, 1.7f));
		mTransform->SetScale(Vector3(0.32f, 0.32f, 1.0f));

		mGeddyPos = PlayerManager::GetPlayer()->GetPlayerPos();
		mGeddyPos.y -= 0.06f;
		mTransform->SetPosition(mGeddyPos);
		mBulletPos = mTransform->GetPosition();

		Collider2D* mCollider = AddComponent<Collider2D>();
		mCollider->SetType(eColliderType::Rect);
		mCollider->SetSize(Vector2(0.1f, 0.1f));


		std::shared_ptr<AudioClip> geddybulletclip = std::make_shared<AudioClip>();
		geddybulletclip->Load(L"..\\Resources\\Audio\\shoot2.wav");
		Resources::Insert<AudioClip>(L"Geddybullet", geddybulletclip);

		geddybulletclip->Play();

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

		mPosition = mTransform->GetPosition();


		if (mIsAttack == true)
		{
			
		}

		if (!mIsDirectionSet && Input::GetKey(eKeyCode::LBTN))
		{
			mMousePos = Input::GetMousePosition();
			float mouseX = (2.0f * mMousePos.x) / application.GetWidth() - 1.0f;
			float mouseY = 1.0f - (2.0f * mMousePos.y) / application.GetHeight();
			Vector4 ndcPos = Vector4(mouseX, mouseY, 0.0f, 1.0f);
			Matrix viewMatrix = Camera::GetGpuViewMatrix();
			Matrix inverseViewMatrix = viewMatrix.Invert();
			Vector4 viewPos = Vector4::Transform(ndcPos, inverseViewMatrix);
			mMousePos = Vector2(viewPos.x, viewPos.y);

			mDirection = mMousePos - mBulletPos;
			mDirection.Normalize();


			float angle = std::atan2(mDirection.y, mDirection.x) * 180.0f / XM_PI;

			mTransform->SetRotation(Vector3(0.0f, 0.0f, angle));

			mIsDirectionSet = true;
		}

		if (mIsDirectionSet)
		{
			Vector2 velocity = mDirection * mSpeed;
			mTransform->SetPosition(mTransform->GetPosition() + Vector3(velocity.x, velocity.y, 0.0f) * Time::DeltaTime());
		}

		mDeadTime += Time::DeltaTime();

		if (this != nullptr)
		{
			if (mDeadTime >= 3.0f)
			{
				Death();
			}
		}

		

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