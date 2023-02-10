#pragma once

namespace jh::enums
{

	enum class eLayerType
	{
		None = 0,
		Monster,
		Player,
		End = 16,
	};

	enum class eComponentType
	{
		None,
		Transform,
		Camera,
		Mesh,
		Collider,
		UI,
		Script,
		End,
	};

	enum class eResourceType
	{
		Mesh,
		Texture,
		Material,
		Sound,
		Prefab,
		MeshData,
		GraphicShader,
		ComputeShader,
		Script,
		End,
	};

}

