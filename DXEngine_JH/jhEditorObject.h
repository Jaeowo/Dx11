#pragma once
#include "..\Engine_SOURCE\jhGameObject.h"

namespace jh
{
	class EditorObject
		: public GameObject
	{
	public:
		EditorObject();
		virtual ~EditorObject();

		virtual void Initalize();
		virtual void Update();
		virtual void FixedUpdate();
		virtual void Render();

	private:
	};

}

