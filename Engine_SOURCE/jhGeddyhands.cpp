#include "jhGeddyhands.h"
#include "jhAnimator.h"
#include "jhResources.h"
#include "jhTransform.h"
#include "jhTime.h"
#include "jhInput.h"
#include "jhCamera.h"
#include "jhApplication.h"
#include "jhGeddyBullet.h"
#include "jhObject.h"
#include "jhSpriteRenderer.h"
#include "jhPlayerManager.h"
#include "jhGeddy.h"

extern jh::Application application;


namespace jh
{
	Geddyhands::Geddyhands()
		:mCount(0)
		,mGeddyhandsState(eGeddyhandsState::Stop)
		,mTime(0.0f)
	{
		mAnimator = AddComponent<Animator>();
		mTransform = GetComponent<Transform>();

		std::shared_ptr<Texture> geddyhandstexture = Resources::Load<Texture>(L"GeddyArm", L"Geddy\\arm96x32.png");
		mAnimator->Create(L"Stop", geddyhandstexture, Vector2(0.0f, 0.0f), Vector2(96.0f, 32.0f), Vector2::Zero, 1, 0.25f);
		mAnimator->Create(L"Shoot1", geddyhandstexture, Vector2(0.0f, 0.0f), Vector2(96.0f, 32.0f), Vector2::Zero, 5, 0.25f);

		mAnimator->Play(L"Stop", true);

		SpriteRenderer* geddyhandssr = AddComponent<SpriteRenderer>();
		std::shared_ptr<Mesh> geddyhandsmesh = Resources::Find<Mesh>(L"RectMesh");
		std::shared_ptr<Material> geddyhandsmaterial = Resources::Find<Material>(L"GeddyArmmaterial");
		geddyhandssr->SetMaterial(geddyhandsmaterial);
		geddyhandssr->SetMesh(geddyhandsmesh);

		mTransform->SetPosition(Vector3(0.887f, 0.823f, 1.7f));
		mTransform->SetScale(Vector3(0.32f, 0.32f, 1.0f));

		mAngle = mTransform->GetRotation();

		mPos = mTransform->GetPosition();



		mGeddyTransform = PlayerManager::GetGeddy()->getTransform();

	}
	Geddyhands::~Geddyhands()
	{
		
	}
	void Geddyhands::Initalize()
	{

		GameObject::Initalize();
	}

	void Geddyhands::Update()
	{
		

		mTransform = GetComponent<Transform>();

		mPos = mTransform->GetPosition();
		mMousePos = Input::GetMousePosition();

		float mouseX = (2.0f * mMousePos.x) / application.GetWidth() - 1.0f;
		float mouseY = 1.0f - (2.0f * mMousePos.y) / application.GetHeight();

		Vector4 ndcPos = Vector4(mouseX, mouseY, 0.0f, 1.0f);

		Matrix viewMatrix = Camera::GetGpuViewMatrix();
		Matrix inverseViewMatrix = viewMatrix.Invert();

		Vector4 viewPos = Vector4::Transform(ndcPos, inverseViewMatrix);

		mMousePos = Vector2(viewPos.x, viewPos.y);

		Vector3 parentPos = mGeddyTransform->GetPosition();
		float dx = mMousePos.x - parentPos.x;
		float dy = mMousePos.y - parentPos.y;
		float angle = atan2(dy, dx) * 180.0f / XM_PI;

		Matrix parentWorldMatrix = mGeddyTransform->GetWorldMatrix();
		Matrix parentWorldMatrixInverse = parentWorldMatrix.Invert();
		Vector3 localMousePos = Vector3::Transform(Vector3(mMousePos.x, mMousePos.y, 0.0f), parentWorldMatrixInverse);

		dx = localMousePos.x - mPos.x;
		dy = localMousePos.y - mPos.y;
		angle = atan2(dy, dx) * 180.0f / XM_PI;

		mAngle.z = angle;

		mTransform->SetRotation(mAngle);

		mTransform->SetParent(mGeddyTransform);
		mTransform->SetPosition(Vector3(-0.05f, -0.105f, 0.0f));
		mTransform->SetScale(Vector3(0.9f, 0.9f, 1.0f));


		switch (mGeddyhandsState)
		{
		case jh::eGeddyhandsState::Stop:
			Stop();
			break;
		case jh::eGeddyhandsState::Shoot:
			Shoot();
			break;
		default:
			break;
		}
	/*	if (PlayerManager::GetGeddy()->GetGeddyState() == eGeddyState::Idle)
		{
			if (this != nullptr)
			{
				this->Death();
			}
		}*/

		GameObject::Update();
	}
	void Geddyhands::FixedUpdate()
	{
		GameObject::FixedUpdate();
	}
	void Geddyhands::Render()
	{
		GameObject::Render();
	}
	void Geddyhands::Shoot()
	{
		if (mCount == 0)
		{
			mAnimator->Play(L"Shoot1", false);
			mCount = 1;
		}
		mTime += Time::DeltaTime();
		if (mTime >= 0.5f)
		{
			mGeddyhandsState = eGeddyhandsState::Stop;
			mCount = 0;
			mTime = 0.0f;
		}
	}
	void Geddyhands::Stop()
	{
		if (mCount == 0)
		{
			mAnimator->Play(L"Stop", false);
			mCount = 1;
		}
	}
}