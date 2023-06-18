#include "jhCaveScene2.h"
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
#include "jhStoneDoor.h"
#include "jhButton.h"
#include "jhMouseCursor.h"
#include "jhNumber.h"
#include "jhNumberTens.h"
#include "jhHpBar.h"
#include "jhWall.h"
#include "jhCollisionManager.h"

namespace jh
{
	CaveScene2::CaveScene2()
		: Scene(eSceneType::Cave2)
	{

	}

	CaveScene2::~CaveScene2()
	{
	}

	void CaveScene2::Initalize()
	{
		;

		Scene::Initalize();
	}

	void CaveScene2::Update()
	{
		if (Input::GetKeyDown(eKeyCode::N))
		{
			SceneManager::LoadScene(eSceneType::Jungle);
		}

		Scene::Update();
	}

	void CaveScene2::FixedUpdate()
	{
		Scene::FixedUpdate();
	}

	void CaveScene2::Render()
	{
		Scene::Render();
	}

	void CaveScene2::OnEnter()
	{

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

		// UI Camera
		GameObject* cameraUIObj = object::Instantiate<GameObject>(eLayerType::Camera);
		Camera* cameraUIComp = cameraUIObj->AddComponent<Camera>();
		cameraUIComp->SetProjectionType(Camera::eProjectionType::Orthographic);
		cameraUIComp->DisableLayerMasks();
		cameraUIComp->TurnLayerMask(eLayerType::UI, true);

		//Cursor
		MouseCursor* mousecursor = object::Instantiate<MouseCursor>(eLayerType::Effect);

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

#pragma region GROUND
		Ground* groundObj9 = object::Instantiate<Ground>(eLayerType::BackGround);
		Transform* groundTr9 = groundObj9->GetComponent<Transform>();
		groundTr9->SetPosition(Vector3(0.5f, -0.955f, 1.7f));
		groundTr9->SetScale(Vector3(0.3f, 0.001f, 1.0f));

		Ground* groundObj8 = object::Instantiate<Ground>(eLayerType::BackGround);
		Transform* groundTr8 = groundObj8->GetComponent<Transform>();
		groundTr8->SetPosition(Vector3(1.2f, -1.07f, 1.7f));
		groundTr8->SetScale(Vector3(1.7f, 0.001f, 1.0f));

		Ground* groundObj7 = object::Instantiate<Ground>(eLayerType::BackGround);
		Transform* groundTr7 = groundObj7->GetComponent<Transform>();
		groundTr7->SetPosition(Vector3(1.2f, 0.32f, 1.7f));
		groundTr7->SetScale(Vector3(0.41f, 0.001f, 1.0f));

		Ground* groundObj6 = object::Instantiate<Ground>(eLayerType::BackGround);
		Transform* groundTr6 = groundObj6->GetComponent<Transform>();
		groundTr6->SetPosition(Vector3(-0.24f, 0.32f, 1.7f));
		groundTr6->SetScale(Vector3(1.72f, 0.001f, 1.0f));

		Ground* groundObj5 = object::Instantiate<Ground>(eLayerType::BackGround);
		Transform* groundTr5 = groundObj5->GetComponent<Transform>();
		groundTr5->SetPosition(Vector3(-1.74f, 0.0f, 1.7f));
		groundTr5->SetScale(Vector3(0.45f, 0.001f, 1.0f));

		Ground* groundObj4 = object::Instantiate<Ground>(eLayerType::BackGround);
		Transform* groundTr4 = groundObj4->GetComponent<Transform>();
		groundTr4->SetPosition(Vector3(-0.6f, -1.67f, 1.7f));
		groundTr4->SetScale(Vector3(0.5f, 0.001f, 1.0f));

		Ground* groundObj3 = object::Instantiate<Ground>(eLayerType::BackGround);
		Transform* groundTr3 = groundObj3->GetComponent<Transform>();
		groundTr3->SetPosition(Vector3(-0.93f, -1.35f, 1.7f));
		groundTr3->SetScale(Vector3(0.3f, 0.001f, 1.0f));

		Ground* groundObj2 = object::Instantiate<Ground>(eLayerType::BackGround);
		Transform* groundTr2 = groundObj2->GetComponent<Transform>();
		groundTr2->SetPosition(Vector3(-1.23f, -1.018f, 1.7f));
		groundTr2->SetScale(Vector3(0.5f, 0.001f, 1.0f));

		Ground* groundObj1 = object::Instantiate<Ground>(eLayerType::BackGround);
		Transform* groundTr1 = groundObj1->GetComponent<Transform>();
		groundTr1->SetPosition(Vector3(-2.13f, -0.36f, 1.7f));
		groundTr1->SetScale(Vector3(1.3f, 0.001f, 1.0f));
#pragma endregion

#pragma region WALL
		Wall* wallObj19 = object::Instantiate<Wall>(eLayerType::BackGround);
		Transform* wallTr19 = wallObj19->GetComponent<Transform>();
		wallTr19->SetPosition(Vector3(1.53f, -0.67f, 1.7f));
		wallTr19->SetScale(Vector3(1.1f, 0.01f, 1.0f));

		Wall* wallObj18 = object::Instantiate<Wall>(eLayerType::BackGround);
		Transform* wallTr18 = wallObj18->GetComponent<Transform>();
		wallTr18->SetPosition(Vector3(0.5f, -0.67f, 1.7f));
		wallTr18->SetScale(Vector3(0.25f, 0.01f, 1.0f));

		Wall* wallObj17 = object::Instantiate<Wall>(eLayerType::BackGround);
		Transform* wallTr17 = wallObj17->GetComponent<Transform>();
		wallTr17->SetPosition(Vector3(-0.7f, -0.39f, 1.7f));
		wallTr17->SetScale(Vector3(0.8f, 0.01f, 1.0f));

		Wall* wallObj16 = object::Instantiate<Wall>(eLayerType::BackGround);
		Transform* wallTr16 = wallObj16->GetComponent<Transform>();
		wallTr16->SetPosition(Vector3(0.2f, 0.61f, 1.7f));
		wallTr16->SetScale(Vector3(2.6f, 0.01f, 1.0f));

		Wall* wallObj15 = object::Instantiate<Wall>(eLayerType::BackGround);
		Transform* wallTr15 = wallObj15->GetComponent<Transform>();
		wallTr15->SetPosition(Vector3(-2.0f, 0.68f, 1.7f));
		wallTr15->SetScale(Vector3(1.0f, 0.01f, 1.0f));

		Wall* wallObj14 = object::Instantiate<Wall>(eLayerType::BackGround);
		Transform* wallTr14 = wallObj14->GetComponent<Transform>();
		wallTr14->SetPosition(Vector3(0.63f, -1.06f, 1.7f));
		wallTr14->SetScale(Vector3(0.01f, 0.2f, 1.0f));

		Wall* wallObj13 = object::Instantiate<Wall>(eLayerType::BackGround);
		Transform* wallTr13 = wallObj13->GetComponent<Transform>();
		wallTr13->SetPosition(Vector3(0.42f, -0.8f, 1.7f));
		wallTr13->SetScale(Vector3(0.01f, 0.4f, 1.0f));

		Wall* wallObj12 = object::Instantiate<Wall>(eLayerType::BackGround);
		Transform* wallTr12 = wallObj12->GetComponent<Transform>();
		wallTr12->SetPosition(Vector3(0.63f, -0.2f, 1.7f));
		wallTr12->SetScale(Vector3(0.01f, 0.9f, 1.0f));

		Wall* wallObj11 = object::Instantiate<Wall>(eLayerType::BackGround);
		Transform* wallTr11 = wallObj11->GetComponent<Transform>();
		wallTr11->SetPosition(Vector3(0.99f, -0.2f, 1.7f));
		wallTr11->SetScale(Vector3(0.01f, 0.9f, 1.0f));

		Wall* wallObj10 = object::Instantiate<Wall>(eLayerType::BackGround);
		Transform* wallTr10 = wallObj10->GetComponent<Transform>();
		wallTr10->SetPosition(Vector3(1.4f, 0.5f, 1.7f));
		wallTr10->SetScale(Vector3(0.01f, 0.6f, 1.0f));

		Wall* wallObj9 = object::Instantiate<Wall>(eLayerType::BackGround);
		Transform* wallTr9 = wallObj9->GetComponent<Transform>();
		wallTr9->SetPosition(Vector3(-1.1f, 1.0f, 1.7f));
		wallTr9->SetScale(Vector3(0.01f, 0.8f, 1.0f));

		Wall* wallObj8 = object::Instantiate<Wall>(eLayerType::BackGround);
		Transform* wallTr8 = wallObj8->GetComponent<Transform>();
		wallTr8->SetPosition(Vector3(-1.1f, -0.05f, 1.7f));
		wallTr8->SetScale(Vector3(0.01f, 0.7f, 1.0f));

		Wall* wallObj7 = object::Instantiate<Wall>(eLayerType::BackGround);
		Transform* wallTr7 = wallObj7->GetComponent<Transform>();
		wallTr7->SetPosition(Vector3(-0.4f, -1.0f, 1.7f));
		wallTr7->SetScale(Vector3(0.01f, 1.4f, 1.0f));

		Wall* wallObj6 = object::Instantiate<Wall>(eLayerType::BackGround);
		Transform* wallTr6 = wallObj6->GetComponent<Transform>();
		wallTr6->SetPosition(Vector3(-0.8f, -1.56f, 1.7f));
		wallTr6->SetScale(Vector3(0.01f, 0.4f, 1.0f));

		Wall* wallObj5 = object::Instantiate<Wall>(eLayerType::BackGround);
		Transform* wallTr5 = wallObj5->GetComponent<Transform>();
		wallTr5->SetPosition(Vector3(-1.0f, -1.23f, 1.7f));
		wallTr5->SetScale(Vector3(0.01f, 0.4f, 1.0f));

		Wall* wallObj4 = object::Instantiate<Wall>(eLayerType::BackGround);
		Transform* wallTr4 = wallObj4->GetComponent<Transform>();
		wallTr4->SetPosition(Vector3(-1.46f, -0.74f, 1.7f));
		wallTr4->SetScale(Vector3(0.01f, 0.71f, 1.0f));

		Wall* wallObj3 = object::Instantiate<Wall>(eLayerType::BackGround);
		Transform* wallTr3 = wallObj3->GetComponent<Transform>();
		wallTr3->SetPosition(Vector3(-1.46f, 0.7f, 1.7f));
		wallTr3->SetScale(Vector3(0.01f, 1.4f, 1.0f));

		Wall* wallObj2 = object::Instantiate<Wall>(eLayerType::BackGround);
		Transform* wallTr2 = wallObj2->GetComponent<Transform>();
		wallTr2->SetPosition(Vector3(-1.51f, 0.5f, 1.7f));
		wallTr2->SetScale(Vector3(0.01f, 1.0f, 1.0f));

		Wall* wallObj1 = object::Instantiate<Wall>(eLayerType::BackGround);
		Transform* wallTr1 = wallObj1->GetComponent<Transform>();
		wallTr1->SetPosition(Vector3(-2.5f, 0.0f, 1.7f));
		wallTr1->SetScale(Vector3(0.01f, 1.5f, 1.0f));
#pragma endregion
		//Total BackGround
		GameObject* cavescene2Obj = object::Instantiate<GameObject>(eLayerType::BackGround);
		Transform* CaveScene2Tr = cavescene2Obj->GetComponent<Transform>();
		CaveScene2Tr->SetPosition(Vector3(-0.7f, 0.0f, 1.7f));
		CaveScene2Tr->SetScale(Vector3(5.5f, 4.0f, 1.0f));


		SpriteRenderer* tilefloorsr = cavescene2Obj->AddComponent<SpriteRenderer>();
		std::shared_ptr<Mesh> tilefloormesh = Resources::Find<Mesh>(L"RectMesh");
		std::shared_ptr<Material> tilefloormaterial = Resources::Find<Material>(L"Cavematerial");
		tilefloorsr->SetMaterial(tilefloormaterial);
		tilefloorsr->SetMesh(tilefloormesh);

		//Player
		mplayer = object::Instantiate<Player>(eLayerType::Player);
		PlayerManager::SetPlayer(mplayer);
		mplayer->SetCoin(PlayerManager::GetPlayer()->GetCoin());
		cameraComp->SetTarget(mplayer);
		PlayerManager::LoadPlayerState(mplayer);
		mplayer->SetPlayerPos(Vector3(-2.13f, -0.27f, 1.7f));



		StoneDoor* stoneDoorObj = object::Instantiate<StoneDoor>(eLayerType::BackGround);
		stoneDoorObj->SetPosition(Vector3(-1.275f, 0.3f, 1.7f));
		stoneDoorObj->SetScale(Vector3(0.45f, 0.45f, 1.0f));
		stoneDoorObj->SetRotation(Vector3(0.0f, 0.0f, 270.0f));
		stoneDoorObj->SetCenter(Vector2(0.0f, -0.04f));

		StoneDoor* stoneDoorObj2 = object::Instantiate<StoneDoor>(eLayerType::BackGround);
		stoneDoorObj2->SetPosition(Vector3(0.8f, 0.3f, 1.7f));
		stoneDoorObj2->SetScale(Vector3(0.45f, 0.47f, 1.0f));
		stoneDoorObj2->SetRotation(Vector3(0.0f, 0.0f, 270.0f));
		stoneDoorObj2->SetCenter(Vector2(0.0f, -0.04f));

		StoneDoor* stoneDoorObj3 = object::Instantiate<StoneDoor>(eLayerType::BackGround);
		stoneDoorObj3->SetPosition(Vector3(1.2f, -0.88f, 1.7f));
		stoneDoorObj3->SetScale(Vector3(0.45f, 0.47f, 1.0f));
		stoneDoorObj3->SetRotation(Vector3(0.0f, 0.0f, 180.0f));
		stoneDoorObj3->SetCenter(Vector2(-0.05f, 0.0f));

		Button* buttonObj = object::Instantiate<Button>(eLayerType::BackGround);
		buttonObj->SetPosition(Vector3(-1.8f, 0.02f, 1.7f));

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

	void CaveScene2::OnExit()
	{
		PlayerManager::SavePlayerState(mplayer);
	}

}