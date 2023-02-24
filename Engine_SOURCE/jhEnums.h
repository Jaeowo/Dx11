#pragma once

namespace jh::enums
{

	enum class eLayerType
	{
		None = 0,
		Camera,
		Grid,
		Monster,
		Player,
		Effect,

		UI,
		End = 16,
	};

	enum class eComponentType
	{
		None,
		Transform, 
		Camera,
		Mesh,
		Collider,
		MeshRenderer,
		SpriteRenderer,
		UI,
		FadeOut,
		FadeIn,
		Script,
		End,
	};

	enum class eResourceType
	{
		Mesh,
		Texture,
		Material,
		Sound,
		/*Font,*/
		Prefab,
		MeshData,
		GraphicShader,
		ComputeShader,
		Script,
		End,
	};


}

