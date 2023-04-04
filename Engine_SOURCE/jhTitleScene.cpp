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
#include "jhAnimator.h"
#include "jhLight.h"
#include "jhPaintShader.h"

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
		//Paint Shader 
		std::shared_ptr<PaintShader> paintShader = Resources::Find<PaintShader>(L"PaintShader");
		//L"SmileTexture"
		std::shared_ptr<Texture> paintTex = Resources::Find<Texture>(L"PaintTexture");
		paintShader->SetTarget(paintTex);
		paintShader->OnExcute();

		//SMILE RECT
		{
			//Player* obj = object::Instantiate<Player>(eLayerType::Player);
			//obj->SetName(L"SMILE");
			//Transform* tr = obj->GetComponent<Transform>();
			//tr->SetPosition(Vector3(2.0f, 0.0f, 5.0f));
			////tr->SetScale(Vector3(2.0f, 1.0f, 1.0f));
			////tr->SetRotation(Vector3(0.0f, 0.0f, XM_PIDIV2 / 2.0f));
			////tr->SetScale(Vector3(1.0f, 1.0f, 1.0f));
			//Collider2D* collider = obj->AddComponent<Collider2D>();
			//collider->SetSize(Vector2(2.0f, 2.0f));
			//collider->SetType(eColliderType::Rect);
			////collider->SetCenter(Vector2(0.2f, 0.2f));
			////collider->SetSize(Vector2(1.5f, 1.5f));

			//SpriteRenderer* mr = obj->AddComponent<SpriteRenderer>();
			//std::shared_ptr<Material> mateiral = Resources::Find<Material>(L"RectMaterial");
			//mr->SetMaterial(mateiral);
			//std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");
			//mr->SetMesh(mesh);
			//object::DontDestroyOnLoad(obj);
		}

		{
			GameObject* directionalLight = object::Instantiate<GameObject>(eLayerType::Player);
			directionalLight->GetComponent<Transform>()->SetPosition(Vector3(0.0f, 0.0f, -100.0f));
			Light* lightComp = directionalLight->AddComponent<Light>();
			lightComp->SetType(eLightType::Directional);
			lightComp->SetDiffuse(Vector4(1.0f, 1.0f, 1.0f, 1.0f));
		}

		{
			GameObject* directionalLight = object::Instantiate<GameObject>(eLayerType::Player);
			directionalLight->GetComponent<Transform>()->SetPosition(Vector3(3.0f, 0.0f, 0.0f));
			Light* lightComp = directionalLight->AddComponent<Light>();
			lightComp->SetType(eLightType::Point);
			lightComp->SetRadius(10.0f);
			lightComp->SetDiffuse(Vector4(0.0f, 0.0f, 0.0f, 0.0f));
		}

		// Main Camera Game Object
		GameObject* cameraObj = object::Instantiate<GameObject>(eLayerType::Camera);
		Camera* cameraComp = cameraObj->AddComponent<Camera>();
		//cameraComp->RegisterCameraInRenderer();
		cameraComp->TurnLayerMask(eLayerType::UI, false);
		cameraObj->AddComponent<CameraScript>();
		mainCamera = cameraComp;
		//renderer::cameras[0] = cameraComp;

		// Ground2 Camera
		GameObject* cameraUIObj = object::Instantiate<GameObject>(eLayerType::Camera);
		Camera* cameraUIComp = cameraUIObj->AddComponent<Camera>();
		cameraUIComp->SetProjectionType(Camera::eProjectionType::Orthographic);
		cameraUIComp->DisableLayerMasks();
		cameraUIComp->TurnLayerMask(eLayerType::BackGround2, true);

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

		Animator* animator = logoObj->AddComponent<Animator>();
		std::shared_ptr<Texture> logotexture = Resources::Load<Texture>(L"logo", L"Title Screen\\owlboyLogoDemo_201x103_strip5.png");
		animator->Create(L"logo", logotexture, Vector2(0.0f, 0.0f), Vector2(201.0f, 103.0f), Vector2::Zero, 13, 0.25f);
		animator->Play(L"logo", true);

		//LeftOtus
		GameObject* LeftOtusObj = object::Instantiate<GameObject>(eLayerType::BackGround);
		LeftOtusObj->SetName(L"LeftOtus");
		Transform* LeftOtusTr = LeftOtusObj->GetComponent<Transform>();
		LeftOtusTr->SetPosition(Vector3(0.465f, 1.13f, 1.7f));
		LeftOtusTr->SetScale(Vector3(0.4f, 0.4f, 1.0f));

		SpriteRenderer* LeftOtussr = LeftOtusObj->AddComponent<SpriteRenderer>();
		std::shared_ptr<Mesh> LeftOtusmesh = Resources::Find<Mesh>(L"RectMesh");
		std::shared_ptr<Material> leftotusmaterial = Resources::Find<Material>(L"LeftOtusmaterial");
		LeftOtussr->SetMaterial(leftotusmaterial);
		LeftOtussr->SetMesh(LeftOtusmesh);

		Animator* Lanimator = LeftOtusObj->AddComponent<Animator>();
		std::shared_ptr<Texture> leftotustexture = Resources::Load<Texture>(L"LOtus", L"Title Screen\\sprOtus_245x137_strip6.png");
		Lanimator->Create(L"LOtus", leftotustexture, Vector2(0.0f, 0.0f), Vector2(245.0f, 137.0f), Vector2::Zero, 6, 0.25f);
		Lanimator->Play(L"LOtus", true);

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

		//Scene::Initalize();
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