#pragma once
#include"jhGameObject.h"
namespace jh
{

	class MousePos
		: public GameObject
	{
	public:
		MousePos();
		virtual ~MousePos();

		virtual void Initalize();
		virtual void Update();
		virtual void FixedUpdate();
		virtual void Render();



	private:
		Matrix mView;
		Matrix mProjection;

		float mNear;
		float mFar;
		float mScale;

		float mAspectRatio;

		static math::Vector2 mousePos;
	};
}
