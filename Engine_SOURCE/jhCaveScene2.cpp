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
		Ground* groundObj2 = object::Instantiate<Ground>(eLayerType::BackGround);
		Transform* groundTr2 = groundObj2->GetComponent<Transform>();
		groundTr2->SetPosition(Vector3(1.2f, -0.56f, 1.7f));
		groundTr2->SetScale(Vector3(1.3f, 0.001f, 1.0f));
#pragma endregion

#pragma region WALL
#pragma endregion
		//Total BackGround
		GameObject* cavescene2Obj = object::Instantiate<GameObject>(eLayerType::BackGround);
		Transform* CaveScene2Tr = cavescene2Obj->GetComponent<Transform>();
		CaveScene2Tr->SetPosition(Vector3(0.0f, 0.0f, 1.7f));
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
		mplayer->SetPlayerPos(Vector3(0.0f, 0.0f, 1.7f));



		StoneDoor* stoneDoorObj = object::Instantiate<StoneDoor>(eLayerType::BackGround);
		stoneDoorObj->SetPosition(Vector3(-1.275f, 0.3f, 1.7f));
		stoneDoorObj->SetScale(Vector3(0.45f, 0.45f, 1.0f));
		stoneDoorObj->SetRotation(Vector3(0.0f, 0.0f, 270.0f));
		stoneDoorObj->SetCenter(Vector2(0.0f, -0.04f));

		StoneDoor* stoneDoorObj2 = object::Instantiate<StoneDoor>(eLayerType::BackGround);
		stoneDoorObj2->SetPosition(Vector3(1.25f, 0.3f, 1.7f));
		stoneDoorObj2->SetScale(Vector3(0.45f, 0.47f, 1.0f));
		stoneDoorObj2->SetRotation(Vector3(0.0f, 0.0f, 270.0f));
		stoneDoorObj2->SetCenter(Vector2(0.0f, -0.04f));

		StoneDoor* stoneDoorObj3 = object::Instantiate<StoneDoor>(eLayerType::BackGround);
		stoneDoorObj3->SetPosition(Vector3(1.8f, -0.88f, 1.7f));
		stoneDoorObj3->SetScale(Vector3(0.45f, 0.47f, 1.0f));
		stoneDoorObj3->SetRotation(Vector3(0.0f, 0.0f, 180.0f));
		stoneDoorObj3->SetCenter(Vector2(-0.05f, 0.0f));

		Button* buttonObj = object::Instantiate<Button>(eLayerType::BackGround);
		buttonObj->SetPosition(Vector3(-1.8f, 0.02f, 1.7f));
	}

	void CaveScene2::OnExit()
	{
		PlayerManager::SavePlayerState(mplayer);
	}

}