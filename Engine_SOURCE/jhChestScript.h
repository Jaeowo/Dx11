#pragma once
#include "jhScript.h"

namespace jh
{
	class Chest;

	class ChestScript
		: public Script
	{
	public:

		ChestScript();
		~ChestScript();

		virtual void Initalize() override;
		virtual void Update() override;
		virtual void Render() override;

		virtual void OnCollisionEnter(Collider2D* collider) override;
		virtual void OnCollisionStay(Collider2D* collider) override;
		virtual void OnCollisionExit(Collider2D* collider) override;

	private:
		Chest* mchest;
		Transform* mPlayerTransform;
	};
}



