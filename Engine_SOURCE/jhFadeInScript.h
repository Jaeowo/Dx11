#pragma once
#include "jhScript.h"

namespace jh
{
	class FadeInScript
		: public Script
	{
	public:
		FadeInScript();
		virtual ~FadeInScript();

		virtual void Initalize();
		virtual void Update();
		virtual void FixedUpdate();
		virtual void Render();

	private:
		float mAmount;
	};
}


