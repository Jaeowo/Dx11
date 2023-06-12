#pragma once
#include "jhGameObject.h"

namespace jh
{
	class Transform;
	class Collider;

	class PlayerAttackCol
		: public GameObject
	{
	public:
		PlayerAttackCol();
		virtual ~PlayerAttackCol();

		virtual void Initalize();
		virtual void Update();
		virtual void FixedUpdate();
		virtual void Render();

	private:
		Vector3 mPlayerPos;
		Collider2D* mCollider;
		Transform* mTransform;

	};
}