#pragma once
#include "jhGameObject.h"

namespace jh
{
	class Transform;
	class Collider;

	class EventTrigger
		: public GameObject
	{
	public:
		EventTrigger();
		virtual ~EventTrigger();

		virtual void Initalize();
		virtual void Update();
		virtual void FixedUpdate();
		virtual void Render();

		void SetColPos(Vector3 pos) { mPos = pos; }

	private:
		Vector3 mPos;
		Collider2D* mCollider;
		Transform* mTransform;

	};
}