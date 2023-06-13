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
	}

	void CaveScene2::OnExit()
	{

	}

}