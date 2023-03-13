#include "jhMovingHandScript.h"
#include "jhInput.h"

namespace jh
{
	MovingHandScript::MovingHandScript()
	{
	}
	MovingHandScript::~MovingHandScript()
	{
	}
	void MovingHandScript::Initalize()
	{
	}
	void MovingHandScript::Update()
	{
		Input::GetMousPosition();
	}
	void MovingHandScript::Render()
	{
	}
	void MovingHandScript::OnCollisionEnter(Collider2D* collider)
	{
	}
	void MovingHandScript::OnCollisionStay(Collider2D* collider)
	{
	}
	void MovingHandScript::OnCollisionExit(Collider2D* collider)
	{
	}
}