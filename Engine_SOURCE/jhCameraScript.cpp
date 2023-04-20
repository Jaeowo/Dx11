#include "jhCameraScript.h"
#include "jhTransform.h"
#include "jhGameObject.h"
#include "jhInput.h"
#include "jhTime.h"
#include "jhCamera.h"
#include "jhObject.h"

namespace jh
{
	CameraScript::CameraScript()
		: Script()
		, mEditorMode(false)
	{
	}
	CameraScript::~CameraScript()
	{
	}
	void CameraScript::Initalize()
	{
	}
	void CameraScript::Update()
	{
		Transform* tr = GetOwner()->GetComponent<Transform>();
		Camera* cameraobj = GetOwner()->GetComponent<Camera>();

		
		Transform* cameraTransform = GetOwner()->GetComponent<Transform>();
		Vector3 cameraposition;

		if(cameraobj->GetTarget() != nullptr && mEditorMode == false)
		{
			Transform* targetTransform = cameraobj->GetTarget()->GetComponent<Transform>();
			Vector3 targetposition = targetTransform->GetPosition();
		
			targetposition.y += 0.1f;
			targetposition.z -= 0.7f;
			cameraposition = targetTransform->Right();
			cameraTransform->SetPosition(targetposition);
		}

		if (mEditorMode == true)
		{
			cameraposition.x = 1.0f;
			cameraposition.y = 1.2f;
			cameraposition.z = 0.2f;
			
			cameraTransform->SetPosition(cameraposition);

		}

		

	


	
	}
	void CameraScript::Render()
	{
	}
}