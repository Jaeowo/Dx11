#include "jhTitleScene.h"
#include "jhTransform.h"
#include "jhMeshRenderer.h"
#include "jhRenderer.h"
#include "jhResources.h"
#include "jhTexture.h"
#include "jhPlayerScript.h"
#include "jhCamera.h"
#include "jhCameraScript.h"
#include "jhSpriteRenderer.h"
#include "jhGridScript.h"
#include "jhObject.h"
#include "jhInput.h"
#include "jhCollider2D.h"
#include "jhPlayer.h"
#include "jhMonster.h"
#include "jhCollisionManager.h"

namespace jh
{
	TitleScene::TitleScene()
		: Scene(eSceneType::Title)
	{
	}
	TitleScene::~TitleScene()
	{
	}
	void TitleScene::Initalize()
	{

		// Main Camera Game Object
		GameObject* cameraObj = object::Instantiate<GameObject>(eLayerType::Camera);
		Camera* cameraComp = cameraObj->AddComponent<Camera>();
		//cameraComp->RegisterCameraInRenderer();
		cameraComp->TurnLayerMask(eLayerType::UI, false);
		cameraObj->AddComponent<CameraScript>();
		mainCamera = cameraComp;
		//renderer::cameras[0] = cameraComp;

		// UI Camera
		//GameObject* cameraUIObj = object::Instantiate<GameObject>(eLayerType::Camera);
		//Camera* cameraUIComp = cameraUIObj->AddComponent<Camera>();
		//cameraUIComp->SetProjectionType(Camera::eProjectionType::Orthographic);
		//cameraUIComp->DisableLayerMasks();
		//cameraUIComp->TurnLayerMask(eLayerType::UI, true);

		// Sky
		GameObject* titleskyObj = object::Instantiate<GameObject>(eLayerType::BackGround);
		titleskyObj->SetName(L"TitleSky");
		Transform* skyTr = titleskyObj->GetComponent<Transform>();
		skyTr->SetPosition(Vector3(1.0f, 0.9f, 1.7f));
		skyTr->SetScale(Vector3(1.5f, 1.1f, 1.0f));

		SpriteRenderer* sr = titleskyObj->AddComponent<SpriteRenderer>();
		std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");
		std::shared_ptr<Material> titleskymaterial = Resources::Find<Material>(L"Titleskymaterial");
		sr->SetMaterial(titleskymaterial);
		sr->SetMesh(mesh);

		//Logo
		//나중에 애니메이션으로 바꿔줘야함 / Title Screen 폴더 안에 있음
		GameObject* logoObj = object::Instantiate<GameObject>(eLayerType::BackGround);
		logoObj->SetName(L"TitleLogo");
		Transform* logoTr = logoObj->GetComponent<Transform>();
		logoTr->SetPosition(Vector3(1.0f, 1.2f, 1.7f));
		logoTr->SetScale(Vector3(0.3f, 0.3f, 1.0f));

		SpriteRenderer* logosr = logoObj->AddComponent<SpriteRenderer>();
		std::shared_ptr<Mesh> logomesh = Resources::Find<Mesh>(L"RectMesh");
		std::shared_ptr<Material> owlboylogomaterial = Resources::Find<Material>(L"OwlboyLogomaterial");
		logosr->SetMaterial(owlboylogomaterial);
		logosr->SetMesh(logomesh);

		//Right
		GameObject* rightObj = object::Instantiate<GameObject>(eLayerType::BackGround);
		rightObj->SetName(L"TitleRight");
		Transform* rightObjTr = rightObj->GetComponent<Transform>();
		rightObjTr->SetPosition(Vector3(1.45f, 0.8f, 1.7f));
		rightObjTr->SetScale(Vector3(0.45f, 0.45f, 1.0f));

		SpriteRenderer* rightsr = rightObj->AddComponent<SpriteRenderer>();
		std::shared_ptr<Mesh> rightmesh = Resources::Find<Mesh>(L"RectMesh");
		std::shared_ptr<Material> titlerightmaterial = Resources::Find<Material>(L"TitleRightmaterial");
		rightsr->SetMaterial(titlerightmaterial);
		rightsr->SetMesh(rightmesh);
		
		//Left
		GameObject* leftObj = object::Instantiate<GameObject>(eLayerType::BackGround);
		leftObj->SetName(L"TitleLeft");
		Transform* leftTr = leftObj->GetComponent<Transform>();
		leftTr->SetPosition(Vector3(0.5f, 0.7f, 1.7f));
		leftTr->SetScale(Vector3(0.6f, 0.6f, 1.0f));

		SpriteRenderer* leftsr = leftObj->AddComponent<SpriteRenderer>();
		std::shared_ptr<Mesh> leftmesh = Resources::Find<Mesh>(L"RectMesh");
		std::shared_ptr<Material> titleleftmaterial = Resources::Find<Material>(L"TitleLeftmaterial");
		leftsr->SetMaterial(titleleftmaterial);
		leftsr->SetMesh(leftmesh);

		Scene::Initalize();
	}
	void TitleScene::Update()
	{
		if (Input::GetKeyDown(eKeyCode::N))
		{
			SceneManager::LoadScene(eSceneType::Play);
		}
		Scene::Update();
	}
	void TitleScene::FixedUpdate()
	{
		Scene::FixedUpdate();
	}
	void TitleScene::Render()
	{
		Scene::Render();
	}
	void TitleScene::OnEnter()
	{
	}
	void TitleScene::OnExit()
	{
	}
}