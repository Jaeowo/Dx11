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

extern jh::Application application;


namespace jh
{
	Geddyhands::Geddyhands()
	{
		Animator* mAnimator = AddComponent<Animator>();
		mTransform = GetComponent<Transform>();

		std::shared_ptr<Texture> geddyhandstexture = Resources::Load<Texture>(L"GeddyArm", L"Geddy\\arm96x32.png");
		mAnimator->Create(L"Stop", geddyhandstexture, Vector2(0.0f, 0.0f), Vector2(96.0f, 32.0f), Vector2::Zero, 1, 0.25f);
		mAnimator->Create(L"Shoot1", geddyhandstexture, Vector2(0.0f, 0.0f), Vector2(96.0f, 32.0f), Vector2::Zero, 5, 0.25f);

		mAnimator->Play(L"Stop", true);

		mTransform->SetPosition(Vector3(0.887f, 0.823f, 1.7f));
		mTransform->SetScale(Vector3(0.32f, 0.32f, 1.0f));

		mAngle = mTransform->GetRotation();
		
		mPos = mTransform->GetPosition();
		
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
		//마우스 좌표를 스크린 좌표계에서 [-1,1] 범위로 변환
		float mouseX = (2.0f * mMousePos.x) / application.GetWidth() - 1.0f;
		float mouseY = 1.0f - (2.0f * mMousePos.y) / application.GetHeight();

		//NDC 좌표로 변환
		Vector4 ndcPos = Vector4(mouseX, mouseY, 0.0f, 1.0f);

		//vew matrix 역행렬 구하기
		Matrix viewMatrix = Camera::GetGpuViewMatrix();
		Matrix inverseViewMatrix = viewMatrix.Invert();

		//NDC 좌표를 view matrix 좌표계로 변환

		Vector4 viewPos = Vector4::Transform(ndcPos, inverseViewMatrix);

		mMousePos = Vector2(viewPos.x, viewPos.y);

		float dx = mMousePos.x - mPos.x;
		float dy = mMousePos.y - mPos.y;
		float angle = atan2(dy, dx) * 180.0f / XM_PI;

		mAngle.z = angle;

		mTransform->SetRotation(mAngle);


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
}