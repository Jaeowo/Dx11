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

		// Player
		Player* playerObj = object::Instantiate<Player>(eLayerType::Player);
		playerObj->SetName(L"Player");
		Transform* PlayerTr = playerObj->GetComponent<Transform>();
		PlayerTr->SetPosition(Vector3(1.0f, 0.8f, 1.7f));
		PlayerTr->SetScale(Vector3(0.35f, 0.35f, 1.0f));
		//PlayerTr
		playerObj->AddComponent<PlayerScript>();

		SpriteRenderer* standsr = playerObj->AddComponent<SpriteRenderer>();
		std::shared_ptr<Mesh> standmesh = Resources::Find<Mesh>(L"RectMesh");
		std::shared_ptr<Material> standmaterial = Resources::Find<Material>(L"Standmaterial");
		standsr->SetMaterial(standmaterial);
		standsr->SetMesh(standmesh);

		Animator* animator = playerObj->AddComponent<Animator>();
		std::shared_ptr<Texture> herotexture = Resources::Load<Texture>(L"hero", L"Otus\\hero.png");
		std::shared_ptr<Texture> hero2texture = Resources::Load<Texture>(L"hero2", L"Otus\\hero2.png");
		std::shared_ptr<Texture> flyUpStartCarrytexture = Resources::Load<Texture>(L"FlyUpStartCarry", L"Otus\\flyUpStartCarry_strip8.png");
		std::shared_ptr<Texture> FlyGrabtexture = Resources::Load<Texture>(L"FlyGrab", L"Otus\\sprFlyGrab_strip11.png");
		std::shared_ptr<Texture> SpreadWingstexture = Resources::Load<Texture>(L"SpreadWings", L"Otus\\sprOtusSpreadWings_112x96_strip9.png");
		std::shared_ptr<Texture> EnterDoortexture = Resources::Load<Texture>(L"EnterDoor", L"Otus\\sprOtusEnterDoor_112x96_strip13.png");
		std::shared_ptr<Texture> Dietexture = Resources::Load<Texture>(L"Die", L"Otus\\sprOtusDie_112x96_strip12.png");
		std::shared_ptr<Texture> Eattexture = Resources::Load<Texture>(L"Eat", L"Otus\\eat_strip14.png");

		animator->Create(L"Idle", herotexture, Vector2(0.0f, 0.0f), Vector2(112.0f, 96.0f), Vector2::Zero, 13, 0.25f);
		animator->Create(L"MoveRight", herotexture, Vector2(0.0f, 96.0f), Vector2(112.0f, 96.0f), Vector2::Zero, 12, 0.2f);
		animator->Create(L"Flying", herotexture, Vector2(0.0f, 192.0f), Vector2(112.0f, 96.0f), Vector2::Zero, 11, 0.2f);
		animator->Create(L"Jump", herotexture, Vector2(0.0f, 384.0f), Vector2(112.0f, 96.0f), Vector2::Zero, 3, 0.2f);
		animator->Create(L"JumpDown", herotexture, Vector2(0.0f, 480.0f), Vector2(112.0f, 96.0f), Vector2::Zero, 5, 0.2f);
		animator->Create(L"hurt", hero2texture, Vector2(0.0f, 288.0f), Vector2(112.0f, 96.0f), Vector2::Zero, 1, 0.2f);
		animator->Create(L"flyinghurt", hero2texture, Vector2(0.0f, 384.0f), Vector2(112.0f, 96.0f), Vector2::Zero, 1, 0.2f);
		animator->Create(L"StartAttack", hero2texture, Vector2(0.0f, 1056.0f), Vector2(112.0f, 96.0f), Vector2::Zero, 6, 0.12f);
		animator->Create(L"Attacking", hero2texture, Vector2(0.0f, 1152.0f), Vector2(112.0f, 96.0f), Vector2::Zero, 9, 0.12f);
		animator->Create(L"FlyUpStartCarry", flyUpStartCarrytexture, Vector2(0.0f, 0.0f), Vector2(112.0f, 96.0f), Vector2::Zero, 8, 0.12f);
		animator->Create(L"FlyGrab", FlyGrabtexture, Vector2(0.0f, 0.0f), Vector2(112.0f, 96.0f), Vector2::Zero, 11, 0.12f);
		animator->Create(L"SpreadWings", SpreadWingstexture, Vector2(0.0f, 0.0f), Vector2(112.0f, 96.0f), Vector2::Zero, 9, 0.15f);
		animator->Create(L"EnterDoor", EnterDoortexture, Vector2(0.0f, 0.0f), Vector2(112.0f, 96.0f), Vector2::Zero, 13, 0.15f);
		animator->Create(L"Die", Dietexture, Vector2(0.0f, 0.0f), Vector2(112.0f, 96.0f), Vector2::Zero, 12, 0.15f);
		animator->Create(L"Eat", Eattexture, Vector2(0.0f, 0.0f), Vector2(112.0f, 96.0f), Vector2::Zero, 14, 0.15f);

		animator->Play(L"Idle", true);

		//if(ePlayerState::Jump)
	
		
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