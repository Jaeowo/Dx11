#include "jhPlayScene.h"
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
#include "jhPlayer.h"
#include "jhCloudScript.h"

namespace jh
{
	PlayScene::PlayScene()
		: Scene(eSceneType::Play)
	{

	}

	PlayScene::~PlayScene()
	{
	}

	void PlayScene::Initalize()
	{
		

		// UI Camera
		//GameObject* cameraUIObj = object::Instantiate<GameObject>(eLayerType::Camera);
		//Camera* cameraUIComp = cameraUIObj->AddComponent<Camera>();
		//cameraUIComp->SetProjectionType(Camera::eProjectionType::Orthographic);
		//cameraUIComp->DisableLayerMasks();
		//cameraUIComp->TurnLayerMask(eLayerType::UI, true);





		Scene::Initalize();
	}

	void PlayScene::Update()
	{
		if (Input::GetKeyDown(eKeyCode::N))
		{
			SceneManager::LoadScene(eSceneType::Title);
		}

		Scene::Update();
	}

	void PlayScene::FixedUpdate()
	{
		Scene::FixedUpdate();
	}

	void PlayScene::Render()
	{
		Scene::Render();
	}

	void PlayScene::OnEnter()
	{

		GameObject* cameraObj = object::Instantiate<GameObject>(eLayerType::Camera, this);
		Camera* cameraComp = cameraObj->AddComponent<Camera>();
		//cameraComp->RegisterCameraInRenderer();
		cameraComp->TurnLayerMask(eLayerType::UI, false);
		cameraObj->AddComponent<CameraScript>();
		mainCamera = cameraComp;

		// UI Camera
		GameObject* cameraUIObj = object::Instantiate<GameObject>(eLayerType::Camera);
		Camera* cameraUIComp = cameraUIObj->AddComponent<Camera>();
		cameraUIComp->SetProjectionType(Camera::eProjectionType::Orthographic);
		cameraUIComp->DisableLayerMasks();
		cameraUIComp->TurnLayerMask(eLayerType::UI, true);

		// Sky
		GameObject* backskyObj = object::Instantiate<GameObject>(eLayerType::BackGround);
		backskyObj->SetName(L"BackSky");
		Transform* backskyTr = backskyObj->GetComponent<Transform>();
		backskyTr->SetPosition(Vector3(1.0f, 1.1f, 1.7f));
		backskyTr->SetScale(Vector3(1.5f, 1.5f, 1.0f));

		SpriteRenderer* backskysr = backskyObj->AddComponent<SpriteRenderer>();
		std::shared_ptr<Mesh> backskymesh = Resources::Find<Mesh>(L"RectMesh");
		std::shared_ptr<Material> backskymaterial = Resources::Find<Material>(L"Backskymaterial");
		backskysr->SetMaterial(backskymaterial);
		backskysr->SetMesh(backskymesh);

		// Stand - 나중에 Animation으로 변경필요
		GameObject* standObj = object::Instantiate<GameObject>(eLayerType::Player);
		standObj->SetName(L"Stand");
		Transform* standTr = standObj->GetComponent<Transform>();
		standTr->SetPosition(Vector3(1.0f, 0.8f, 1.7f));
		standTr->SetScale(Vector3(0.2f, 0.2f, 1.0f));

		SpriteRenderer* standsr = standObj->AddComponent<SpriteRenderer>();
		std::shared_ptr<Mesh> standmesh = Resources::Find<Mesh>(L"RectMesh");
		std::shared_ptr<Material> standmaterial = Resources::Find<Material>(L"Standmaterial");
		standsr->SetMaterial(standmaterial);
		standsr->SetMesh(standmesh);

		standObj->AddComponent<PlayerScript>();

		// hpbar
		GameObject* hpBar = object::Instantiate<GameObject>(eLayerType::UI);
		hpBar->SetName(L"HPBAR");
		Transform* hpBarTR = hpBar->GetComponent<Transform>();
		hpBarTR->SetPosition(Vector3(-5.5f, 4.5f, 1.0f));
		hpBarTR->SetScale(Vector3(2.0f, 0.5f, 1.0f));

		SpriteRenderer* hpsr = hpBar->AddComponent<SpriteRenderer>();
		hpBar->AddComponent(hpsr);
		std::shared_ptr<Mesh> hpmesh = Resources::Find<Mesh>(L"RectMesh");
		std::shared_ptr<Material> hpspriteMaterial = Resources::Find<Material>(L"Hpbarmaterial");
		hpsr->SetMesh(hpmesh);
		hpsr->SetMaterial(hpspriteMaterial);

		// tilefloor
		GameObject* tilefloorObj = object::Instantiate<GameObject>(eLayerType::BackGround);
		tilefloorObj->SetName(L"Tilefloor");
		Transform* tilefloorTr = tilefloorObj->GetComponent<Transform>();
		tilefloorTr->SetPosition(Vector3(1.0f, 0.7f, 1.7f));
		tilefloorTr->SetScale(Vector3(0.3f, 0.1f, 1.0f));

		SpriteRenderer* tilefloorsr = tilefloorObj->AddComponent<SpriteRenderer>();
		std::shared_ptr<Mesh> tilefloormesh = Resources::Find<Mesh>(L"RectMesh");
		std::shared_ptr<Material> tilefloormaterial = Resources::Find<Material>(L"Tilefloormaterial");
		tilefloorsr->SetMaterial(tilefloormaterial);
		tilefloorsr->SetMesh(tilefloormesh);

		// TopProp
		GameObject* toppropObj = object::Instantiate<GameObject>(eLayerType::BackGround);
		toppropObj->SetName(L"TopProp");
		Transform* toppropTr = toppropObj->GetComponent<Transform>();
		toppropTr->SetPosition(Vector3(1.3f, 1.2f, 1.7f));
		toppropTr->SetScale(Vector3(0.4f, 0.2f, 1.0f));

		SpriteRenderer* toppropsr = toppropObj->AddComponent<SpriteRenderer>();
		std::shared_ptr<Mesh> toppropmesh = Resources::Find<Mesh>(L"RectMesh");
		std::shared_ptr<Material> toppropmaterial = Resources::Find<Material>(L"TopProp08material");
		toppropsr->SetMaterial(toppropmaterial);
		toppropsr->SetMesh(toppropmesh);

		toppropObj->AddComponent<CloudScript>();
	}

	void PlayScene::OnExit()
	{
	}

}