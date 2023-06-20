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
#include "jhHpBar.h"
#include "jhNumber.h"
#include "jhNumberTens.h"
#include "jhWall.h"
#include "jhEventTrigger.h"
#include "jhInput.h"
#include "jhTime.h"
#include "jhFadeInScript.h"
#include "jhJungleDoor.h"

namespace jh
{
	CaveScene::CaveScene()
		: Scene(eSceneType::Cave)
		, mCount(false)
		, mTime(0.0f)
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
		if (Input::GetKeyDown(eKeyCode::N))
		{
			SceneManager::LoadScene(eSceneType::Cave2);
		}
		Scene::Update();

		if (mplayer->GetCaveEventTrigger() == true)
		{
			if (mCount == false)
			{
				GameObject* FadeInObject = object::Instantiate<GameObject>(eLayerType::UI);
				MeshRenderer* FadeInMr = FadeInObject->AddComponent<MeshRenderer>();
				FadeInMr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
				FadeInMr->SetMaterial(Resources::Find<Material>(L"FadeInMaterial"));
				FadeInObject->AddComponent<FadeInScript>();
				Transform* fadetr = FadeInObject->GetComponent<Transform>();
				fadetr->SetPosition(Vector3(0.0f, 0.0f, 1.0f));
				fadetr->SetScale(Vector3(25.0f, 25.0f, 1.0f));

				mtortoise->SetPlayerState(eTortoiseState::MaskMove);
				mtortoise->SetAniCheck(false);
				mCount = true;
			}

		}
		
	
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
		mTime += Time::DeltaTime();

		GameObject* directionalLight = object::Instantiate<GameObject>(eLayerType::Player);
		directionalLight->GetComponent<Transform>()->SetPosition(Vector3(0.0f, 0.0f, -100.0f));
		Light* lightComp = directionalLight->AddComponent<Light>();
		lightComp->SetType(eLightType::Directional);
		lightComp->SetDiffuse(Vector4(1.0f, 1.0f, 1.0f, 1.0f));

		//Main Camera
		mcamera = object::Instantiate<GameObject>(eLayerType::Camera, this);
		mcameracomp = mcamera->AddComponent<Camera>();
		mcameracomp->TurnLayerMask(eLayerType::UI, false);
		mcamera->AddComponent<CameraScript>();
		mainCamera = mcameracomp;

		// UI Camera
		GameObject* cameraUIObj = object::Instantiate<GameObject>(eLayerType::Camera);
		Camera* cameraUIComp = cameraUIObj->AddComponent<Camera>();
		cameraUIComp->SetProjectionType(Camera::eProjectionType::Orthographic);
		cameraUIComp->DisableLayerMasks();
		cameraUIComp->TurnLayerMask(eLayerType::UI, true);

		//Cursor
		MouseCursor* mousecursor = object::Instantiate<MouseCursor>(eLayerType::Effect);

		//EventTrigger
		EventTrigger* eventtriggerObj = object::Instantiate<EventTrigger>(eLayerType::BackGround);
		Transform* eventtriggerTr = eventtriggerObj->GetComponent<Transform>();
		eventtriggerTr->SetPosition(Vector3(-1.5f, -1.65f, 1.7f));
		eventtriggerTr->SetScale(Vector3(1.5f, 0.8f, 1.0f));

#pragma region WALL

		Wall* wallObj7 = object::Instantiate<Wall>(eLayerType::BackGround);
		Transform* wallTr7 = wallObj7->GetComponent<Transform>();
		wallTr7->SetPosition(Vector3(0.26f, -0.31f, 1.7f));
		wallTr7->SetScale(Vector3(0.01f, 0.35f, 1.0f));
		wallTr7->SetRotation(Vector3(0.0f, 0.0f, 320.0f));

		Wall* wallObj6 = object::Instantiate<Wall>(eLayerType::BackGround);
		Transform* wallTr6 = wallObj6->GetComponent<Transform>();
		wallTr6->SetPosition(Vector3(1.3f, -0.35f, 1.7f));
		wallTr6->SetScale(Vector3(0.01f, 0.45f, 1.0f));

		Wall* wallObj5 = object::Instantiate<Wall>(eLayerType::BackGround);
		Transform* wallTr5 = wallObj5->GetComponent<Transform>();
		wallTr5->SetPosition(Vector3(0.55f, -0.8f, 1.7f));
		wallTr5->SetScale(Vector3(0.01f, 0.45f, 1.0f));

		Wall* wallObj4 = object::Instantiate<Wall>(eLayerType::BackGround);
		Transform* wallTr4 = wallObj4->GetComponent<Transform>();
		wallTr4->SetPosition(Vector3(-0.4f, -0.46f, 1.7f));
		wallTr4->SetScale(Vector3(1.13f, 0.01f, 1.0f));

		Wall* wallObj3 = object::Instantiate<Wall>(eLayerType::BackGround);
		Transform* wallTr3 = wallObj3->GetComponent<Transform>();
		wallTr3->SetPosition(Vector3(1.1f, -0.22f, 1.7f));
		wallTr3->SetScale(Vector3(1.53f, 0.01f, 1.0f));

		Wall* wallObj2 = object::Instantiate<Wall>(eLayerType::BackGround);
		Transform* wallTr2 = wallObj2->GetComponent<Transform>();
		wallTr2->SetPosition(Vector3(-0.9f, -1.85f, 1.7f));
		wallTr2->SetScale(Vector3(0.01f, 1.63f, 1.0f));

		Wall* wallObj1 = object::Instantiate<Wall>(eLayerType::BackGround);
		Transform* wallTr1 = wallObj1->GetComponent<Transform>();
		wallTr1->SetPosition(Vector3(-2.2f, -1.5f, 1.7f));
		wallTr1->SetScale(Vector3(0.01f, 2.3f, 1.0f)); 


#pragma endregion

		GameObject* WallObj = object::Instantiate<GameObject>(eLayerType::BackGround2);
		Transform* WallTr = WallObj->GetComponent<Transform>();
		WallTr->SetPosition(Vector3(0.0f, 3.5f, 1.7f));
		WallTr->SetScale(Vector3(2.9f, 2.9f, 1.0f));

		SpriteRenderer* wallsr = WallObj->AddComponent<SpriteRenderer>();
		std::shared_ptr<Mesh> wallmesh = Resources::Find<Mesh>(L"RectMesh");
		std::shared_ptr<Material> wallmaterial = Resources::Find<Material>(L"WallMaterial");
		wallsr->SetMaterial(wallmaterial);
		wallsr->SetMesh(wallmesh);
		WallObj->AddComponent<BackSkyScript>();


		//tile
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
		mplayer = object::Instantiate<Player>(eLayerType::Player);
		PlayerManager::SetPlayer(mplayer);
		mplayer->SetCoin(PlayerManager::GetPlayer()->GetCoin());
		mcameracomp->SetTarget(mplayer);
		PlayerManager::LoadPlayerState(mplayer);

		Geddy* geddyObj = object::Instantiate<Geddy>(eLayerType::Friends);
		PlayerManager::SetGeddy(geddyObj);
		geddyObj->SetCount(0);
		geddyObj->AddComponent<GeddyScript>();

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
		Transform* gawkTr = gawkObj->GetComponent<Transform>();
		gawkTr->SetPosition(Vector3(-0.5f, -0.5f, 1.7f));
		gawkTr->SetScale(Vector3(0.29f, 0.29f, 1.0f));

		mtortoise = object::Instantiate<Tortoise>(eLayerType::Monster);
		mtortoise->SetPosition(Vector3(-1.2f, -2.53f, 1.7f));



#pragma region UI
		// coin UI
		GameObject* hpBar = object::Instantiate<GameObject>(eLayerType::UI);
		Transform* hpBarTR = hpBar->GetComponent<Transform>();
		hpBarTR->SetPosition(Vector3(-6.2f, 4.2f, 1.0f));
		hpBarTR->SetScale(Vector3(0.25f, 0.25f, 1.0f));

		SpriteRenderer* hpsr = hpBar->AddComponent<SpriteRenderer>();
		hpBar->AddComponent(hpsr);
		std::shared_ptr<Mesh> hpmesh = Resources::Find<Mesh>(L"RectMesh");
		std::shared_ptr<Material> hpspriteMaterial = Resources::Find<Material>(L"Coin1Material");
		hpsr->SetMesh(hpmesh);
		hpsr->SetMaterial(hpspriteMaterial);

		HpBar* hpbar = object::Instantiate<HpBar>(eLayerType::UI);
		hpbar->SetPosition(Vector3(-5.5f, 4.5f, 1.0f));

		Number* number = object::Instantiate<Number>(eLayerType::UI);
		number->SetPosition(Vector3(-5.75f, 4.2f, 1.0f));

		NumberTens* numbertens = object::Instantiate<NumberTens>(eLayerType::UI);
		numbertens->SetPosition(Vector3(-5.9f, 4.2f, 1.0f));
#pragma endregion

		CollisionManager::CollisionLayerCheck(eLayerType::Monster, eLayerType::Player, true);
		CollisionManager::CollisionLayerCheck(eLayerType::Monster, eLayerType::PlayerObject, true);
		CollisionManager::CollisionLayerCheck(eLayerType::Monster, eLayerType::MonsterObject, true);
		CollisionManager::CollisionLayerCheck(eLayerType::Monster, eLayerType::BackGround, true);
		CollisionManager::CollisionLayerCheck(eLayerType::BackGround, eLayerType::BackGrouncObj, true);
		CollisionManager::CollisionLayerCheck(eLayerType::BackGround, eLayerType::MonsterObject, true);
		CollisionManager::CollisionLayerCheck(eLayerType::Player, eLayerType::BackGround2, true);
		CollisionManager::CollisionLayerCheck(eLayerType::Player, eLayerType::BackGround, true);
		CollisionManager::CollisionLayerCheck(eLayerType::Player, eLayerType::BackGrouncObj, true);
		CollisionManager::CollisionLayerCheck(eLayerType::Player, eLayerType::Friends, true);
		CollisionManager::CollisionLayerCheck(eLayerType::Friends, eLayerType::BackGround, true);

	}

	void CaveScene::OnExit()
	{
		mplayer->SetCaveEventTrigger(false);
		PlayerManager::SavePlayerState(mplayer);
	}
}