#pragma once
#include "jhScript.h"

namespace jh
{
	class Thrower;

	class ThrowerScript
		: public Script
	{
	public:

		ThrowerScript();
		~ThrowerScript();

		virtual void Initalize() override;
		virtual void Update() override;
		virtual void Render() override;

		virtual void OnCollisionEnter(Collider2D* collider) override;
		virtual void OnCollisionStay(Collider2D* collider) override;
		virtual void OnCollisionExit(Collider2D* collider) override;

	private:
		Thrower* mThrower;
	};
}
