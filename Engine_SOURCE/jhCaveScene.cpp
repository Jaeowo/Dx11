#include "jhCaveScene.h"
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
#include "jhBackSkyScript.h"
#include "jhGround.h"
#include "jhGawk.h"
#include "jhChangeMonsterState.h"
#include "jhGeddy.h"
#include "jhGeddyScript.h"
#include "jhCollisionManager.h"
#include "jhMouseCursor.h"
#include "jhTortoise.h"

#include "jhTortoiseMask.h"

namespace jh
{
	CaveScene::CaveScene()
		: Scene(eSceneType::Cave)
	{
	}
	CaveScene::~CaveScene()
	{
	}
	void CaveScene::Initalize()
	{
		

		Scene::Initalize();
	}
	void CaveScene::Update()
	{
		Scene::Update();
	}
	void CaveScene::FixedUpdate()
	{
		Scene::FixedUpdate();
	}
	void CaveScene::Render()
	{
		Scene::Render();
	}
	void CaveScene::OnEnter()
	{
		//PlayerManager::GetPlayer()->SetPlayerPos(Vector3(0.0f, 0.0f, 1.7f));
		//PlayerManager::GetPlayer()->SetPlayerState(ePlayerState::Idle);
		//PlayerManager::GetPlayer()->SetCount(0);

		//PlayerManager::GetGeddy()->SetCount(0);

		GameObject* directionalLight = object::Instantiate<GameObject>(eLayerType::Player);
		directionalLight->GetComponent<Transform>()->SetPosition(Vector3(0.0f, 0.0f, -100.0f));
		Light* lightComp = directionalLight->AddComponent<Light>();
		lightComp->SetType(eLightType::Directional);
		lightComp->SetDiffuse(Vector4(1.0f, 1.0f, 1.0f, 1.0f));

		//Main Camera
		GameObject* cameraObj = object::Instantiate<GameObject>(eLayerType::Camera, this);
		Camera* cameraComp = cameraObj->AddComponent<Camera>();
		cameraComp->TurnLayerMask(eLayerType::UI, false);
		cameraObj->AddComponent<CameraScript>();
		mainCamera = cameraComp;

		//Cursor
		MouseCursor* mousecursor = object::Instantiate<MouseCursor>(eLayerType::Effect);

		//Wall
		GameObject* WallObj = object::Instantiate<GameObject>(eLayerType::BackGround2);
		Transform* WallTr = WallObj->GetComponent<Transform>();
		WallTr->SetPosition(Vector3(0.0f, 3.5f, 1.7f));
		WallTr->SetScale(Vector3(1.9f, 1.9f, 1.0f));

		SpriteRenderer* wallsr = WallObj->AddComponent<SpriteRenderer>();
		std::shared_ptr<Mesh> wallmesh = Resources::Find<Mesh>(L"RectMesh");
		std::shared_ptr<Material> wallmaterial = Resources::Find<Material>(L"WallMaterial");
		wallsr->SetMaterial(wallmaterial);
		wallsr->SetMesh(wallmesh);
		WallObj->AddComponent<BackSkyScript>();

		//Test
		GameObject* tilefloorObj = object::Instantiate<GameObject>(eLayerType::BackGround);
		tilefloorObj->SetName(L"Tilefloor");
		Transform* tilefloorTr = tilefloorObj->GetComponent<Transform>();
		tilefloorTr->SetPosition(Vector3(-0.9f, -1.383f, 1.7f));
		tilefloorTr->SetScale(Vector3(5.5f, 4.0f, 1.0f));

		SpriteRenderer* tilefloorsr = tilefloorObj->AddComponent<SpriteRenderer>();
		std::shared_ptr<Mesh> tilefloormesh = Resources::Find<Mesh>(L"RectMesh");
		std::shared_ptr<Material> tilefloormaterial = Resources::Find<Material>(L"TotalCaveMaterial");
		tilefloorsr->SetMaterial(tilefloormaterial);
		tilefloorsr->SetMesh(tilefloormesh);

		//Player
		Player* playerObj = object::Instantiate<Player>(eLayerType::Player);
		PlayerManager::SetPlayer(playerObj);
		//playerObj->SetPlayerPos(Vector3(1.0f, 15.0f, 0.0f));
		//playerObj->AddComponent<PlayerScript>();
		cameraComp->SetTarget(playerObj);

		Geddy* geddyObj = object::Instantiate<Geddy>(eLayerType::Player);
		PlayerManager::SetGeddy(geddyObj);
		//playerObj->SetPlayerPos(Vector3(1.0f, 15.0f, 0.0f));
		geddyObj->SetCount(0);
		geddyObj->AddComponent<GeddyScript>();
		//cameraComp->SetTarget(playerObj);

		//ground
		Ground* groundObj4 = object::Instantiate<Ground>(eLayerType::BackGround);
		Transform* groundTr4 = groundObj4->GetComponent<Transform>();
		groundTr4->SetPosition(Vector3(-1.55f, -2.6f, 1.7f));
		groundTr4->SetScale(Vector3(1.25f, 0.001f, 1.0f));

		Ground* groundObj3 = object::Instantiate<Ground>(eLayerType::BackGround);
		Transform* groundTr3 = groundObj3->GetComponent<Transform>();
		groundTr3->SetPosition(Vector3(-0.18f, -0.995f, 1.7f));
		groundTr3->SetScale(Vector3(1.45f, 0.001f, 1.0f));

		Ground* groundObj2 = object::Instantiate<Ground>(eLayerType::BackGround);
		Transform* groundTr2 = groundObj2->GetComponent<Transform>();
		groundTr2->SetPosition(Vector3(1.2f, -0.56f, 1.7f));
		groundTr2->SetScale(Vector3(1.3f, 0.001f, 1.0f));

		//Gawk
		Gawk* gawkObj = object::Instantiate<Gawk>(eLayerType::Monster);
		SpriteRenderer* gawksr = gawkObj->AddComponent<SpriteRenderer>();
		std::shared_ptr<Mesh> gawkmesh = Resources::Find<Mesh>(L"RectMesh");
		std::shared_ptr<Material> gawkmaterial = Resources::Find<Material>(L"GawkMaterial");
		gawksr->SetMaterial(gawkmaterial);
		gawksr->SetMesh(gawkmesh);
		Transform* gawkTr = gawkObj->GetComponent<Transform>();
		gawkTr->SetPosition(Vector3(-0.5f, -0.5f, 1.7f));
		gawkTr->SetScale(Vector3(0.29f, 0.29f, 1.0f));

		Tortoise* tortoiseObj = object::Instantiate<Tortoise>(eLayerType::Monster);
		tortoiseObj->SetPosition(Vector3(-1.35f, -2.53f, 1.7f));

		TortoiseMask* maskObj = object::Instantiate<TortoiseMask>(eLayerType::MonsterObject);
		maskObj->SetPosition(Vector3(-1.35f, -2.53f, 1.7f));

		CollisionManager::CollisionLayerCheck(eLayerType::Monster, eLayerType::PlayerObject, true);
	}
	void CaveScene::OnExit()
	{
	}
}