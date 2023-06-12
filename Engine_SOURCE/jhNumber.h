#pragma once
#include "jhGameObject.h"

namespace jh
{
	class Transform;
	class Animator;

	class Number
		: public GameObject
	{
	public:
		Number();
		virtual ~Number();

		virtual void Initalize();
		virtual void Update();
		virtual void FixedUpdate();
		virtual void Render();

		void SetPosition(Vector3 position) { mPosition = position; }
		void SetCount(bool onecount) { mOneCount = onecount; }

		void SetNumber(int number);
	private:
		Vector3 mPosition;

		Transform* mTransform;
		Animator* mAnimator;

		int mPlayerCoin;
		bool mOneCount;
	};
}