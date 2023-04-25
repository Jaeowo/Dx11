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
#include "jhHorizontal.h"
#include "jhSloped.h"
#include "jhVertical.h"
#include "jhGeddyBullet.h"
#include "jhBackSkyScript.h"

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
		
		//!!!!!!! 코드 너무 길어졌으니 객체들 클래스로 옮겨서 정리하기 !!!!!!
		
		// Horizontal
		Horizontal* horizontalObj = object::Instantiate<Horizontal>(eLayerType::BackGrouncObj);
		Transform* horizontalTr = horizontalObj->GetComponent<Transform>();
		horizontalTr->SetPosition(Vector3(1.5f, 1.0f, 1.7f));
		horizontalTr->SetScale(Vector3(0.16, 0.08f, 1.0f));

		SpriteRenderer* horizontalsr = horizontalObj->AddComponent<SpriteRenderer>();
		std::shared_ptr<Mesh> horizontalmesh = Resources::Find<Mesh>(L"RectMesh");
		std::shared_ptr<Material> horizontalmaterial = Resources::Find<Material>(L"Horizontalmaterial");
		horizontalsr->SetMaterial(horizontalmaterial);
		horizontalsr->SetMesh(horizontalmesh);

		// Sloped
		Sloped* slopedObj = object::Instantiate<Sloped>(eLayerType::BackGrouncObj);
		Transform* slopedTr = slopedObj->GetComponent<Transform>();
		slopedTr->SetPosition(Vector3(1.5f, 0.9f, 1.7f));
		slopedTr->SetScale(Vector3(0.14f, 0.1f, 1.0f));

		SpriteRenderer* slopedsr = slopedObj->AddComponent<SpriteRenderer>();
		std::shared_ptr<Mesh> slopedmesh = Resources::Find<Mesh>(L"RectMesh");
		std::shared_ptr<Material> slopedmaterial = Resources::Find<Material>(L"Slopedmaterial");
		slopedsr->SetMaterial(slopedmaterial);
		slopedsr->SetMesh(slopedmesh);

		// Vertical
		Vertical* verticalObj = object::Instantiate<Vertical>(eLayerType::BackGrouncObj);
		Transform* VerticalTr = verticalObj->GetComponent<Transform>();
		VerticalTr->SetPosition(Vector3(1.5f, 0.8f, 1.7f));
		VerticalTr->SetScale(Vector3(0.1f, 0.13f, 1.0f));

		SpriteRenderer* verticalsr = verticalObj->AddComponent<SpriteRenderer>();
		std::shared_ptr<Mesh> verticalymesh = Resources::Find<Mesh>(L"RectMesh");
		std::shared_ptr<Material> verticalmaterial = Resources::Find<Material>(L"Verticalmaterial");
		verticalsr->SetMaterial(verticalmaterial);
		verticalsr->SetMesh(verticalymesh);

		// Player
		Player* playerObj = object::Instantiate<Player>(eLayerType::Player);
		PlayerManager::SetPlayer(playerObj);
		playerObj->SetName(L"Player");
		playerObj->AddComponent<PlayerScript>();

		cameraComp->SetTarget(playerObj);
	

		//Gawk
		Gawk* gawkObj = object::Instantiate<Gawk>(eLayerType::Monster);
		SpriteRenderer* gawksr = gawkObj->AddComponent<SpriteRenderer>();
		std::shared_ptr<Mesh> gawkmesh = Resources::Find<Mesh>(L"RectMesh");
		std::shared_ptr<Material> gawkmaterial = Resources::Find<Material>(L"GawkMaterial");
		gawksr->SetMaterial(gawkmaterial);
		gawksr->SetMesh(gawkmesh);

		//GeddyHands
		//Geddyhands* geddyhandsObj = object::Instantiate<Geddyhands>(eLayerType::FriendsObject);
		


		//Geddy
		Geddy* geddyObj = object::Instantiate<Geddy>(eLayerType::Friends);
		PlayerManager::SetGeddy(geddyObj);
		geddyObj->AddComponent<GeddyScript>();
		geddyObj->SetName(L"Geddy");


		////GeddyBullet
		//GeddyBullet* geddybulletobj = object::Instantiate<GeddyBullet>(eLayerType::PlayerObject);
		//Transform* geddybulletTr = geddybulletobj->GetComponent<Transform>();
		//geddybulletTr->SetPosition(Vector3(0.5f, 0.9f, 1.7f));
		//geddybulletTr->SetScale(Vector3(0.3f, 0.3f, 1.0f));
		//SpriteRenderer* bulletsr = geddybulletobj->AddComponent<SpriteRenderer>();
		//std::shared_ptr<Mesh> bulletmesh = Resources::Find<Mesh>(L"RectMesh");
		//std::shared_ptr<Material> geddybulletmaterial = Resources::Find<Material>(L"Mechanicbulletmaterial");
		//bulletsr->SetMaterial(geddybulletmaterial);
		//bulletsr->SetMesh(bulletmesh);


		//!!!Ground 클래스에 세부정보 들어가도록 수정하기 !!!
	
		//Ground
		Ground* groundObj = object::Instantiate<Ground>(eLayerType::BackGround);
		Transform* groundTr = groundObj->GetComponent<Transform>();
		groundTr->SetPosition(Vector3(0.99f, 0.734f, 1.7f));
		groundTr->SetScale(Vector3(0.27f, 0.35f, 1.0f));
		groundObj->AddComponent<GroundScript>();
		Collider2D* groundcollider = groundObj->AddComponent<Collider2D>();
		groundcollider->SetType(eColliderType::Rect);
		groundcollider->SetSize(Vector2(1.5f, 0.3f));
		//groundcollider->SetCenter(Vector2(1.0f, 1.0f));

		Ground* groundObj2 = object::Instantiate<Ground>(eLayerType::BackGround);
		Transform* groundTr2 = groundObj2->GetComponent<Transform>();
		groundTr2->SetPosition(Vector3(0.958f, 1.09f, 1.7f));
		groundTr2->SetScale(Vector3(0.159f, 0.1f, 1.0f));
		groundObj2->AddComponent<GroundScript>();
		Collider2D* groundcollider2 = groundObj2->AddComponent<Collider2D>();
		groundcollider2->SetType(eColliderType::Rect);
		groundcollider2->SetSize(Vector2(1.5f, 0.3f));

		Ground* groundObj3 = object::Instantiate<Ground>(eLayerType::BackGround);
		Transform* groundTr3 = groundObj3->GetComponent<Transform>();
		groundTr3->SetPosition(Vector3(0.635f, 0.33f, 1.7f));
		groundTr3->SetScale(Vector3(0.68f, 0.1f, 1.0f));
		groundObj3->AddComponent<GroundScript>();
		Collider2D* groundcollider3 = groundObj3->AddComponent<Collider2D>();
		groundcollider3->SetType(eColliderType::Rect);
		groundcollider3->SetSize(Vector2(1.5f, 0.3f));

		//Flatform
		GameObject* grassfloorObj = object::Instantiate<GameObject>(eLayerType::BackGround);
		Transform* grassfloorTr = grassfloorObj->GetComponent<Transform>();
		grassfloorTr->SetPosition(Vector3(0.3f, 0.3f, 1.7f));
		grassfloorTr->SetScale(Vector3(0.35f, 0.1f, 1.0f));
		SpriteRenderer* grassfloorsr = grassfloorObj->AddComponent<SpriteRenderer>();
		std::shared_ptr<Mesh> grassfloormesh = Resources::Find<Mesh>(L"RectMesh");
		std::shared_ptr<Material> grassfloormaterial = Resources::Find<Material>(L"GrassFloorMaterial");
		grassfloorsr->SetMaterial(grassfloormaterial);
		grassfloorsr->SetMesh(grassfloormesh);

		GameObject* grassfloorObj2 = object::Instantiate<GameObject>(eLayerType::BackGround);
		Transform* grassfloorTr2 = grassfloorObj2->GetComponent<Transform>();
		grassfloorTr2->SetPosition(Vector3(0.64f, 0.3f, 1.7f));
		grassfloorTr2->SetScale(Vector3(0.35f, 0.1f, 1.0f));
		SpriteRenderer* grassfloorsr2 = grassfloorObj2->AddComponent<SpriteRenderer>();
		grassfloorsr2->SetMaterial(grassfloormaterial);
		grassfloorsr2->SetMesh(grassfloormesh);

		GameObject* grassfloorObj3 = object::Instantiate<GameObject>(eLayerType::BackGround);
		Transform* grassfloorTr3 = grassfloorObj3->GetComponent<Transform>();
		grassfloorTr3->SetPosition(Vector3(0.98f, 0.3f, 1.7f));
		grassfloorTr3->SetScale(Vector3(0.35f, 0.1f, 1.0f));
		SpriteRenderer* grassfloorsr3 = grassfloorObj3->AddComponent<SpriteRenderer>();
		grassfloorsr3->SetMaterial(grassfloormaterial);
		grassfloorsr3->SetMesh(grassfloormesh);


		//BackRock3
		GameObject* backrock3Obj = object::Instantiate<GameObject>(eLayerType::BackGround);
		Transform* backrock3Tr = backrock3Obj->GetComponent<Transform>();
		backrock3Tr->SetPosition(Vector3(0.5f, 0.9f, 1.7f));
		backrock3Tr->SetScale(Vector3(0.15f, 0.15f, 1.0f));
		SpriteRenderer* backroc3sr = backrock3Obj->AddComponent<SpriteRenderer>();
		std::shared_ptr<Mesh> backrock3mesh = Resources::Find<Mesh>(L"RectMesh");
		std::shared_ptr<Material> backrock3material = Resources::Find<Material>(L"BackRock3Material");
		backroc3sr->SetMaterial(backrock3material);
		backroc3sr->SetMesh(backrock3mesh);

		//BackRock
		GameObject* backrockObj = object::Instantiate<GameObject>(eLayerType::BackGround);
		Transform* backrockTr = backrockObj->GetComponent<Transform>();
		backrockTr->SetPosition(Vector3(0.5f, 0.8f, 1.7f));
		backrockTr->SetScale(Vector3(0.15f, 0.15f, 1.0f));
		SpriteRenderer* backrocksr = backrockObj->AddComponent<SpriteRenderer>();
		std::shared_ptr<Mesh> backrockmesh = Resources::Find<Mesh>(L"RectMesh");
		std::shared_ptr<Material> backrockmaterial = Resources::Find<Material>(L"BackRockMaterial");
		backrocksr->SetMaterial(backrockmaterial);
		backrocksr->SetMesh(backrockmesh);

		//BackRock2
		GameObject* backrock2Obj = object::Instantiate<GameObject>(eLayerType::BackGround);
		Transform* backrock2Tr = backrock2Obj->GetComponent<Transform>();
		backrock2Tr->SetPosition(Vector3(0.5f, 0.6f, 1.7f));
		backrock2Tr->SetScale(Vector3(0.15f, 0.15f, 1.0f));
		SpriteRenderer* backrock2sr = backrock2Obj->AddComponent<SpriteRenderer>();
		std::shared_ptr<Mesh> backrock2mesh = Resources::Find<Mesh>(L"RectMesh");
		std::shared_ptr<Material> backrock2material = Resources::Find<Material>(L"BackRock2Material");
		backrock2sr->SetMaterial(backrock2material);
		backrock2sr->SetMesh(backrock2mesh);

		// Sky
		GameObject* backskyObj = object::Instantiate<GameObject>(eLayerType::BackGround2);
		Transform* backskyTr = backskyObj->GetComponent<Transform>();
		backskyTr->SetPosition(Vector3(1.0f, 1.1f, 1.7f));
		backskyTr->SetScale(Vector3(2.1f, 2.1f, 1.0f));

		SpriteRenderer* backskysr = backskyObj->AddComponent<SpriteRenderer>();
		std::shared_ptr<Mesh> backskymesh = Resources::Find<Mesh>(L"RectMesh");
		std::shared_ptr<Material> backskymaterial = Resources::Find<Material>(L"Backskymaterial");
		backskysr->SetMaterial(backskymaterial);
		backskysr->SetMesh(backskymesh);
		backskyObj->AddComponent<BackSkyScript>();

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

		// tilefloor
		GameObject* tilefloorObj = object::Instantiate<GameObject>(eLayerType::BackGround);
		tilefloorObj->SetName(L"Tilefloor");
		Transform* tilefloorTr = tilefloorObj->GetComponent<Transform>();
		tilefloorTr->SetPosition(Vector3(1.0f, 0.815f, 1.7f));
		tilefloorTr->SetScale(Vector3(0.5f, 0.7f, 1.0f));

		SpriteRenderer* tilefloorsr = tilefloorObj->AddComponent<SpriteRenderer>();
		std::shared_ptr<Mesh> tilefloormesh = Resources::Find<Mesh>(L"RectMesh");
		std::shared_ptr<Material> tilefloormaterial = Resources::Find<Material>(L"Tilefloormaterial");
		tilefloorsr->SetMaterial(tilefloormaterial);
		tilefloorsr->SetMesh(tilefloormesh);

		CollisionManager::CollisionLayerCheck(eLayerType::Player, eLayerType::BackGround, true);
		CollisionManager::CollisionLayerCheck(eLayerType::Player, eLayerType::Friends, true);
		CollisionManager::CollisionLayerCheck(eLayerType::Friends, eLayerType::BackGround, true);

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

	}

	void PlayScene::OnExit()
	{
	}

}