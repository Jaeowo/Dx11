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
#include "jhAnimator.h"
#include "jhPlayerManager.h"
#include "jhLight.h"
#include "jhGround.h"
#include "jhGroundScript.h"
#include "jhCollider2D.h"
#include "jhCollisionManager.h"
#include "jhGeddy.h"
#include "jhGeddyScript.h"
#include "jhGround.h"
#include "jhGroundScript.h"
#include "jhGeddyhands.h"
#include "jhGawk.h"
#include "jhGeddyBullet.h"
#include "jhBackSkyScript.h"
#include "jhSlope.h"
#include "jhDoor.h"
#include "jhMouseCursor.h"
#include "jhRing.h"
#include "jhChest.h"
#include "jhCoin.h"
#include "jhHpBar.h"
#include "jhWall.h"
#include "jhNumber.h"
#include "jhNumberTens.h"
#include "jhTortoise.h"
#include "jhAudioClip.h"
#include "jhAudioSource.h"


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
		Scene::Initalize();
	}

	void PlayScene::Update()
	{
		if (Input::GetKeyDown(eKeyCode::N))
		{
			SceneManager::LoadScene(eSceneType::Cave);
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
		{
			GameObject* directionalLight = object::Instantiate<GameObject>(eLayerType::Player);
			directionalLight->GetComponent<Transform>()->SetPosition(Vector3(0.0f, 0.0f, -100.0f));
			Light* lightComp = directionalLight->AddComponent<Light>();
			lightComp->SetType(eLightType::Directional);
			lightComp->SetDiffuse(Vector4(1.0f, 1.0f, 1.0f, 1.0f));
		}

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

		//Village
		GameObject* tilefloorObj = object::Instantiate<GameObject>(eLayerType::BackGround);
		tilefloorObj->SetName(L"Tilefloor");
		Transform* tilefloorTr = tilefloorObj->GetComponent<Transform>();
		tilefloorTr->SetPosition(Vector3(1.0f, 0.815f, 1.7f));
		tilefloorTr->SetScale(Vector3(5.5f, 6.0f, 1.0f));

		SpriteRenderer* tilefloorsr = tilefloorObj->AddComponent<SpriteRenderer>();
		std::shared_ptr<Mesh> tilefloormesh = Resources::Find<Mesh>(L"RectMesh");
		std::shared_ptr<Material> tilefloormaterial = Resources::Find<Material>(L"TotalVillageMaterial");
		tilefloorsr->SetMaterial(tilefloormaterial);
		tilefloorsr->SetMesh(tilefloormesh);

		//Door
		Door* DoorObj = object::Instantiate<Door>(eLayerType::BackGround);
		Transform* DoorTr = DoorObj->GetComponent<Transform>();
		DoorTr->SetPosition(Vector3(-0.18f, 2.37f, 1.7f));
		DoorTr->SetScale(Vector3(0.07f, 0.1f, 1.0f));

		// Player
		mplayer = object::Instantiate<Player>(eLayerType::Player);
		PlayerManager::SetPlayer(mplayer);
		//playerObj->AddComponent<PlayerScript>();
		cameraComp->SetTarget(mplayer);


		//Geddy
		Geddy* geddyObj = object::Instantiate<Geddy>(eLayerType::Friends);
		PlayerManager::SetGeddy(geddyObj);
		geddyObj->AddComponent<GeddyScript>();
		geddyObj->SetName(L"Geddy");


		std::shared_ptr<AudioClip> audioClip = Resources::Load<AudioClip>
			(L"Vellie", L"..\\Resources\\Audio\\08. Vellie (Owlboy Theme).mp3");

		maudioSource = tilefloorObj->AddComponent<AudioSource>();
		maudioSource->SetClip(audioClip);
		maudioSource->SetLoop(true);

		maudioSource->Play();


#pragma region RING

		Ring* RingObj = object::Instantiate<Ring>(eLayerType::BackGrouncObj);
		RingObj->SetPosition(Vector3(1.2f, 0.0f, 1.7f));
		RingObj->SetState(eRingSet::horizontal);

		Ring* RingObj2 = object::Instantiate<Ring>(eLayerType::BackGrouncObj);
		RingObj2->SetPosition(Vector3(1.2f, 0.05f, 1.7f));
		RingObj2->SetState(eRingSet::horizontal);

		Ring* RingObj3 = object::Instantiate<Ring>(eLayerType::BackGrouncObj);
		RingObj3->SetPosition(Vector3(1.2f, 0.1f, 1.7f));
		RingObj3->SetState(eRingSet::horizontal);

		Ring* RingObj4 = object::Instantiate<Ring>(eLayerType::BackGrouncObj);
		RingObj4->SetPosition(Vector3(0.6f, 0.4f, 1.7f));
		RingObj4->SetState(eRingSet::Vertical);

		Ring* RingObj5 = object::Instantiate<Ring>(eLayerType::BackGrouncObj);
		RingObj5->SetPosition(Vector3(0.55f, 0.4f, 1.7f));
		RingObj5->SetState(eRingSet::Vertical);

		Ring* RingObj6 = object::Instantiate<Ring>(eLayerType::BackGrouncObj);
		RingObj6->SetPosition(Vector3(0.5f, 0.4f, 1.7f));
		RingObj6->SetState(eRingSet::Vertical);

		Ring* RingObj7 = object::Instantiate<Ring>(eLayerType::BackGrouncObj);
		RingObj7->SetPosition(Vector3(0.1f, 1.5f, 1.7f));
		RingObj7->SetState(eRingSet::Sloped);

		Ring* RingObj8 = object::Instantiate<Ring>(eLayerType::BackGrouncObj);
		RingObj8->SetPosition(Vector3(0.15f, 1.55f, 1.7f));
		RingObj8->SetState(eRingSet::Sloped);

		Ring* RingObj9 = object::Instantiate<Ring>(eLayerType::BackGrouncObj);
		RingObj9->SetPosition(Vector3(0.2f, 1.6f, 1.7f));
		RingObj9->SetState(eRingSet::Sloped);

#pragma endregion
#pragma region GROUND
		Ground* groundObj17 = object::Instantiate<Ground>(eLayerType::BackGround);
		Transform* groundTr17 = groundObj17->GetComponent<Transform>();
		groundTr17->SetPosition(Vector3(-0.12f, 2.33f, 1.7f));
		groundTr17->SetScale(Vector3(0.3f, 0.001f, 1.0f));

		Ground* groundObj16 = object::Instantiate<Ground>(eLayerType::BackGround);
		Transform* groundTr16 = groundObj16->GetComponent<Transform>();
		groundTr16->SetPosition(Vector3(0.72f, 1.935f, 1.7f));
		groundTr16->SetScale(Vector3(0.3f, 0.001f, 1.0f));

		Ground* groundObj15 = object::Instantiate<Ground>(eLayerType::BackGround);
		Transform* groundTr15 = groundObj15->GetComponent<Transform>();
		groundTr15->SetPosition(Vector3(0.815f, -0.17f, 1.7f));
		groundTr15->SetScale(Vector3(0.21f, 0.001f, 1.0f));

		Ground* groundObj14 = object::Instantiate<Ground>(eLayerType::BackGround);
		Transform* groundTr14 = groundObj14->GetComponent<Transform>();
		groundTr14->SetPosition(Vector3(0.84f, -0.53f, 1.7f));
		groundTr14->SetScale(Vector3(0.34f, 0.001f, 1.0f));

		Ground* groundObj13 = object::Instantiate<Ground>(eLayerType::BackGround);
		Transform* groundTr13 = groundObj13->GetComponent<Transform>();
		groundTr13->SetPosition(Vector3(1.96f, -0.74f, 1.7f));
		groundTr13->SetScale(Vector3(0.32f, 0.001f, 1.0f));

		Ground* groundObj12 = object::Instantiate<Ground>(eLayerType::BackGround);
		Transform* groundTr12 = groundObj12->GetComponent<Transform>();
		groundTr12->SetPosition(Vector3(0.35f, -0.87f, 1.7f));
		groundTr12->SetScale(Vector3(0.3f, 0.001f, 1.0f));

		Ground* groundObj11 = object::Instantiate<Ground>(eLayerType::BackGround);
		Transform* groundTr11 = groundObj11->GetComponent<Transform>();
		groundTr11->SetPosition(Vector3(1.75f, -0.81f, 1.7f));
		groundTr11->SetScale(Vector3(0.22f, 0.001f, 1.0f));

		Ground* groundObj10 = object::Instantiate<Ground>(eLayerType::BackGround);
		Transform* groundTr10 = groundObj10->GetComponent<Transform>();
		groundTr10->SetPosition(Vector3(1.1f, -1.54f, 1.7f));
		groundTr10->SetScale(Vector3(0.61f, 0.001f, 1.0f));

		Ground* groundObj9 = object::Instantiate<Ground>(eLayerType::BackGround);
		Transform* groundTr9 = groundObj9->GetComponent<Transform>();
		groundTr9->SetPosition(Vector3(0.32f, -1.795f, 1.7f));
		groundTr9->SetScale(Vector3(0.6f, 0.001f, 1.0f));

		Ground* groundObj8 = object::Instantiate<Ground>(eLayerType::BackGround);
		Transform* groundTr8 = groundObj8->GetComponent<Transform>();
		groundTr8->SetPosition(Vector3(1.73f, -1.83f, 1.7f));
		groundTr8->SetScale(Vector3(0.7f, 0.001f, 1.0f));

		Ground* groundObj7 = object::Instantiate<Ground>(eLayerType::BackGround);
		Transform* groundTr7 = groundObj7->GetComponent<Transform>();
		groundTr7->SetPosition(Vector3(1.73f, 0.28f, 1.7f));
		groundTr7->SetScale(Vector3(0.23f, 0.001f, 1.0f));

		Ground* groundObj6 = object::Instantiate<Ground>(eLayerType::BackGround);
		Transform* groundTr6 = groundObj6->GetComponent<Transform>();
		groundTr6->SetPosition(Vector3(1.5f, 0.335f, 1.7f));
		groundTr6->SetScale(Vector3(0.33f, 0.001f, 1.0f));

		Ground* groundObj5 = object::Instantiate<Ground>(eLayerType::BackGround);
		Transform* groundTr5 = groundObj5->GetComponent<Transform>();
		groundTr5->SetPosition(Vector3(2.1f, 1.28f, 1.7f));
		groundTr5->SetScale(Vector3(0.73f, 0.001f, 1.0f));

		Ground* groundObj4 = object::Instantiate<Ground>(eLayerType::BackGround);
		Transform* groundTr4 = groundObj4->GetComponent<Transform>();
		groundTr4->SetPosition(Vector3(1.55f, 1.44f, 1.7f));
		groundTr4->SetScale(Vector3(0.31f, 0.001f, 1.0f));

		Ground* groundObj3 = object::Instantiate<Ground>(eLayerType::BackGround);
		Transform* groundTr3 = groundObj3->GetComponent<Transform>();
		groundTr3->SetPosition(Vector3(0.53f, 0.8f, 1.7f));
		groundTr3->SetScale(Vector3(0.35f, 0.001f, 1.0f));

		Ground* groundObj2 = object::Instantiate<Ground>(eLayerType::BackGround);
		Transform* groundTr2 = groundObj2->GetComponent<Transform>();
		groundTr2->SetPosition(Vector3(0.4f, 1.0f, 1.7f));
		groundTr2->SetScale(Vector3(0.35f, 0.001f, 1.0f));
#pragma endregion

#pragma region WALL
		Wall* wallObj3 = object::Instantiate<Wall>(eLayerType::BackGround);
		Transform* wallTr3 = wallObj3->GetComponent<Transform>();
		wallTr3->SetPosition(Vector3(2.07f, -1.7f, 1.7f));
		wallTr3->SetScale(Vector3(0.01f, 0.3f, 1.0f));

		Wall* wallObj2 = object::Instantiate<Wall>(eLayerType::BackGround);
		Transform* wallTr2 = wallObj2->GetComponent<Transform>();
		wallTr2->SetPosition(Vector3(1.4f, -1.7f, 1.7f));
		wallTr2->SetScale(Vector3(0.01f, 0.3f, 1.0f));

		Wall* wallObj1 = object::Instantiate<Wall>(eLayerType::BackGround);
		Transform* wallTr1 = wallObj1->GetComponent<Transform>();
		wallTr1->SetPosition(Vector3(0.05f, -1.7f, 1.7f));
		wallTr1->SetScale(Vector3(0.01f, 0.3f, 1.0f));

#pragma endregion
#pragma region SLOPE
		Slope* SlopeObj2 = object::Instantiate<Slope>(eLayerType::BackGround);
		Transform* slopeTr2 = SlopeObj2->GetComponent<Transform>();
		slopeTr2->SetPosition(Vector3(1.73f, 1.35f, 1.7f));
		slopeTr2->SetScale(Vector3(0.25f, 0.01f, 1.0f));
		SlopeObj2->SetLeftUp(true);

		Slope* SlopeObj = object::Instantiate<Slope>(eLayerType::BackGround);
		Transform* slopeTr = SlopeObj->GetComponent<Transform>();
		slopeTr->SetPosition(Vector3(0.7f, -1.678f, 1.7f));
		slopeTr->SetScale(Vector3(0.35f, 0.001f, 1.0f));
		SlopeObj->SetRightUp(true);

#pragma endregion

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

		// Sky
		GameObject* backskyObj = object::Instantiate<GameObject>(eLayerType::BackGround3);
		Transform* backskyTr = backskyObj->GetComponent<Transform>();
		backskyTr->SetPosition(Vector3(1.0f, 1.1f, 1.7f));
		backskyTr->SetScale(Vector3(2.1f, 2.1f, 1.0f));

		SpriteRenderer* backskysr = backskyObj->AddComponent<SpriteRenderer>();
		std::shared_ptr<Mesh> backskymesh = Resources::Find<Mesh>(L"RectMesh");
		std::shared_ptr<Material> backskymaterial = Resources::Find<Material>(L"Backskymaterial");
		backskysr->SetMaterial(backskymaterial);
		backskysr->SetMesh(backskymesh);
		backskyObj->AddComponent<BackSkyScript>();

		Chest* chestObj = object::Instantiate<Chest>(eLayerType::BackGrouncObj);
		chestObj->SetPosition(Vector3(0.35f, -0.82f, 1.7f));

		// TopProp
		GameObject* toppropObj = object::Instantiate<GameObject>(eLayerType::BackGround2);
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


		CollisionManager::CollisionLayerCheck(eLayerType::BackGround, eLayerType::PlayerObject, true);
		CollisionManager::CollisionLayerCheck(eLayerType::BackGround, eLayerType::BackGrouncObj, true);
		CollisionManager::CollisionLayerCheck(eLayerType::Player, eLayerType::BackGround2, true);
		CollisionManager::CollisionLayerCheck(eLayerType::Player, eLayerType::BackGround, true);
		CollisionManager::CollisionLayerCheck(eLayerType::Player, eLayerType::BackGrouncObj, true);
		CollisionManager::CollisionLayerCheck(eLayerType::Player, eLayerType::Friends, true);
		CollisionManager::CollisionLayerCheck(eLayerType::Friends, eLayerType::BackGround, true);
	}

	void PlayScene::OnExit()
	{
		PlayerManager::SavePlayerState(mplayer);
		maudioSource->Stop();
	}

}