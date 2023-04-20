#pragma once
#include "jhGameObject.h"

namespace jh
{
	class Transform;
	class Horizontal
		: public GameObject
	{
	public:
		Horizontal();
		virtual ~Horizontal();

		virtual void Initalize();
		virtual void Update();
		virtual void FixedUpdate();
		virtual void Render();

	private:
		Transform* mTransform;
	};
}


