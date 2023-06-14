#include "jhJungleScene.h"
#include "jhObject.h"
#include "jhLight.h"
#include "jhPlayer.h"
#include "jhCamera.h"
#include "jhCameraScript.h"
#include "jhRenderer.h"
#include "jhTransform.h"
#include "jhMeshRenderer.h"
#include "jhResources.h"
#include "jhSpriteRenderer.h"
#include "jhPlayerManager.h"
#include "jhInput.h"
#include "jhGround.h"

namespace jh
{
	JungleScene::JungleScene()
		: Scene(eSceneType::Jungle)
	{

	}

	JungleScene::~JungleScene()
	{
	}

	void JungleScene::Initalize()
	{
		;

		Scene::Initalize();
	}

	void JungleScene::Update()
	{

		Scene::Update();
	}

	void JungleScene::FixedUpdate()
	{
		Scene::FixedUpdate();
	}

	void JungleScene::Render()
	{
		Scene::Render();
	}

	void JungleScene::OnEnter()
	{
		GameObject* directionalLight = object::Instantiate<GameObject>(eLayerType::Player);
		directionalLight->GetComponent<Transform>()->SetPosition(Vector3(0.0f, 0.0f, -100.0f));
		Light* lightComp = directionalLight->AddComponent<Light>();
		lightComp->SetType(eLightType::Directional);
		lightComp->SetDiffuse(Vector4(0.5f, 0.5f, 0.5f, 0.5f));

		//Main Camera
		GameObject* cameraObj = object::Instantiate<GameObject>(eLayerType::Camera, this);
		Camera* cameraComp = cameraObj->AddComponent<Camera>();
		cameraComp->TurnLayerMask(eLayerType::UI, false);
		cameraObj->AddComponent<CameraScript>();
		mainCamera = cameraComp;

		// UI Camera
		GameObject* cameraUIObj = object::Instantiate<GameObject>(eLayerType::Camera);
		Camera* cameraUIComp = cameraUIObj->AddComponent<Camera>();
		cameraUIComp->SetProjectionType(Camera::eProjectionType::Orthographic);
		cameraUIComp->DisableLayerMasks();
		cameraUIComp->TurnLayerMask(eLayerType::UI, true);

		//Total BackGround
		GameObject* cavescene2Obj = object::Instantiate<GameObject>(eLayerType::BackGround);
		Transform* CaveScene2Tr = cavescene2Obj->GetComponent<Transform>();
		CaveScene2Tr->SetPosition(Vector3(0.0f, 0.0f, 1.7f));
		CaveScene2Tr->SetScale(Vector3(1.5f, 1.0f, 1.0f));

		SpriteRenderer* tilefloorsr = cavescene2Obj->AddComponent<SpriteRenderer>();
		std::shared_ptr<Mesh> tilefloormesh = Resources::Find<Mesh>(L"RectMesh");
		std::shared_ptr<Material> tilefloormaterial = Resources::Find<Material>(L"Junglematerial");
		tilefloorsr->SetMaterial(tilefloormaterial);
		tilefloorsr->SetMesh(tilefloormesh);

		//Player
		Player* playerObj = object::Instantiate<Player>(eLayerType::Player);
		PlayerManager::SetPlayer(playerObj);
		playerObj->SetCoin(PlayerManager::GetPlayer()->GetCoin());
		cameraComp->SetTarget(playerObj);

		Ground* groundObj2 = object::Instantiate<Ground>(eLayerType::BackGround);
		Transform* groundTr2 = groundObj2->GetComponent<Transform>();
		groundTr2->SetPosition(Vector3(1.2f, -0.56f, 1.7f));
		groundTr2->SetScale(Vector3(1.3f, 0.001f, 1.0f));
	}

	void JungleScene::OnExit()
	{

	}

}