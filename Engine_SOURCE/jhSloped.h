#pragma once
#include "jhGameObject.h"
namespace jh
{
	class Transform;
	class Sloped
		: public GameObject
	{
	public:
		Sloped();
		virtual ~Sloped();

		virtual void Initalize();
		virtual void Update();
		virtual void FixedUpdate();
		virtual void Render();

	private:
		Transform* mTransform;
	};
}





