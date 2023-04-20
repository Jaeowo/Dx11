#pragma once
#include "jhGameObject.h"
namespace jh
{
	class Transform;
	class Vertical
		: public GameObject
	{
	public:
		Vertical();
		virtual ~Vertical();

		virtual void Initalize();
		virtual void Update();
		virtual void FixedUpdate();
		virtual void Render();

	private:
		Transform* mTransform;
	};
}


