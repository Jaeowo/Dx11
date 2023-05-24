#pragma once
#include "jhGameObject.h"

namespace jh
{
	class Transform;
	class MouseCursor
		: public GameObject
	{
	public:
		MouseCursor();
		virtual ~MouseCursor();

		virtual void Initalize();
		virtual void Update();
		virtual void FixedUpdate();
		virtual void Render();

	private:
		Transform* mTransform;
	};
}