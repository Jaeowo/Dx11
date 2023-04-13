#include "jhMousePos.h"
#include "jhInput.h"
#include "yaMath.h"
#include "jhApplication.h"
#include "jhTransform.h"

extern jh::Application application;
namespace jh
{
	MousePos::MousePos()
	{
		mousePos = Input::GetMousPosition();
		float ndcX = (2.0f * mousePos.x) / application.GetWidth() - 1.0f;
		float ndcY = 1.0f - (2.0f * mousePos.y) / application.GetHeight();

		//Vector2 ndc = (2.0f * mousePos.x)
	
	}
	MousePos::~MousePos()
	{
	}
	void MousePos::Initalize()
	{
	}
	void MousePos::Update()
	{
	}
	void MousePos::FixedUpdate()
	{
	}
	void MousePos::Render()
	{
	}
	//void MousePos::CreateViewMatrix()
	//{
	//	Transform* tr = GetComponent<Transform>();
	//	Vector3 pos = tr->GetPosition();

	//	// Crate Translate view matrix
	//	mView = Matrix::Identity;
	//	mView *= Matrix::CreateTranslation(-pos);
	//	//회전 정보

	//	Vector3 up = tr->Up();
	//	Vector3 right = tr->Right();
	//	Vector3 foward = tr->Forward();

	//	Matrix viewRotate;
	//	viewRotate._11 = right.x; viewRotate._12 = up.x; viewRotate._13 = foward.x;
	//	viewRotate._21 = right.y; viewRotate._22 = up.y; viewRotate._23 = foward.y;
	//	viewRotate._31 = right.z; viewRotate._32 = up.z; viewRotate._33 = foward.z;

	//	mView *= viewRotate;
	//}

	//void MousePos::CreateProjectionMatrix()
	//{
	//	RECT winRect;
	//	GetClientRect(application.GetHwnd(), &winRect);

	//	float width = (winRect.right - winRect.left) * mScale;
	//	float height = (winRect.bottom - winRect.top) * mScale;
	//	mAspectRatio = width / height;

	//	mProjection = Matrix::CreateOrthographicLH(width / 100.0f, height / 100.0f, mNear, mFar);
	//}
}