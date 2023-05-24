#include "jhMouseCursor.h"
#include "jhTransform.h"
#include "jhSpriteRenderer.h"
#include "jhResources.h"
#include "jhInput.h"
#include "jhApplication.h"

extern jh::Application application;
namespace jh
{
	MouseCursor::MouseCursor()
	{
		mTransform = GetComponent<Transform>();
		SpriteRenderer* geddyhandssr = AddComponent<SpriteRenderer>();
		std::shared_ptr<Mesh> geddyhandsmesh = Resources::Find<Mesh>(L"RectMesh");
		std::shared_ptr<Material> geddyhandsmaterial = Resources::Find<Material>(L"CursorMaterial");
		geddyhandssr->SetMaterial(geddyhandsmaterial);
		geddyhandssr->SetMesh(geddyhandsmesh);

		mTransform->SetScale(Vector3(0.03f, 0.03f, 1.0f));
		ShowCursor(false);
	}
	MouseCursor::~MouseCursor()
	{
	}
	void MouseCursor::Initalize()
	{
		GameObject::Initalize();
	}
	void MouseCursor::Update()
	{
		Vector2 mousePos = Input::GetMousePosition();
		float mouseX = (2.0f * mousePos.x) / application.GetWidth() - 1.0f;
		float mouseY = 1.0f - (2.0f * mousePos.y) / application.GetHeight();
		Vector4 ndcPos = Vector4(mouseX, mouseY, 0.0f, 1.0f);
		Matrix viewMatrix = Camera::GetGpuViewMatrix();
		Matrix inverseViewMatrix = viewMatrix.Invert();
		Vector4 viewPos = Vector4::Transform(ndcPos, inverseViewMatrix);
		mousePos = Vector2(viewPos.x, viewPos.y);

		mTransform->SetPosition(Vector3(mousePos.x, mousePos.y, 1.70001f));
		GameObject::Update();
	}
	void MouseCursor::FixedUpdate()
	{
		GameObject::FixedUpdate();
	}
	void MouseCursor::Render()
	{
		GameObject::Render();
	}
}