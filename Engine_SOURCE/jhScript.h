#pragma once
#include "jhComponent.h"

namespace jh
{
	class Script
		: public Component
	{
	public:
		Script();
		virtual ~Script();

		virtual void Initalize();
		virtual void Update();
		virtual void FixedUpdate();
		virtual void Render();

	private:

	};
}

