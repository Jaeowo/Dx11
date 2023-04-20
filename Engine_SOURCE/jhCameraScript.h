#pragma once
#include "jhScript.h"

namespace jh
{


	class CameraScript
		:public Script
	{
	public:
		CameraScript();
		~CameraScript();

		virtual void Initalize() override;
		virtual void Update() override;
		virtual void Render() override;
	private:
		bool mEditorMode;
	};
}


