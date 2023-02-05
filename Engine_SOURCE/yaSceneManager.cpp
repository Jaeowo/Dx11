#include "yaSceneManager.h"
#include "yaTransform.h"
#include "yaMeshRenderer.h"
#include "yaRenderer.h"
#include "yaResources.h"
#include "yaTexture.h"

namespace ya
{
	Scene* SceneManager::mPlayScene = nullptr;

	void SceneManager::Initalize()
	{
		mPlayScene = new Scene();
		mPlayScene->Initalize();

		GameObject* obj = new GameObject();
		Transform* tr = new Transform();
		tr->SetPosition(Vector3(0.2f, 0.2f, 0.0f));
		obj->AddComponent(tr);

		MeshRenderer* mr = new MeshRenderer();
		obj->AddComponent(mr);

		Shader* shader = Resources::Find<Shader>(L"RectShader");
		Mesh* mesh = Resources::Find<Mesh>(L"RectMesh");

		mr->SetShader(shader);
		mr->SetMesh(mesh);

		Texture* texture = Resources::Load<Texture>(L"SmileTexture", L"smile.png");
		texture->BindShader(eShaderStage::PS, 0);

		mPlayScene->AddGameObject(obj, eLayerType::Player);
	}
	void SceneManager::Update()
	{
		mPlayScene->Update();
	}
	void SceneManager::FixedUpdate()
	{
		mPlayScene->FixedUpdate();
	}
	void SceneManager::Render()
	{
		mPlayScene->Render();
	}
}