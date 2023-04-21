#pragma once

namespace jh::enums
{

	enum class eSceneType
	{
		Title,
		Play,
		End,
	};

	enum class eLayerType
	{
		None = 0,
		Camera,
		BackGround2,
		BackGround,
		Grid,
		Monster,
		Friends,
		FriendsObject,
		Player,
		PlayerObject,
		BackGrouncObj,
		Effect,

		Particle,
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
		Rigidbody,
		SpriteRenderer,
		Animator,
		ParticleSystem,
		Light,
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

	enum class eColliderType
	{
		None,
		Rect,
		Circle,
		Box,
		Sphere,
		End,
	};

	enum class eAnimationType
	{
		None,
		SecondDimension,
		ThirdDimension,
		End,
	};

	enum class eLightType
	{
		Directional,
		Point,
		Spot,
		End,
	};

	enum class ePlayerState
	{
		Idle,
		LeftRun,
		RightRun,
		Jump,
		GroundRoll,

		EnterDoor,

		StartAttack,
		Attacking,

		StartFly, //SpreadWings
		Fly,
		FlyGrab,
		FlyCarry,
		FlyHurt,
		FlyAttack,
		StartFlyRoll,
		FlyRoll,
		Eat,

		Hurt,
		Die,

	};

	enum class eGeddyState
	{
		Idle,
		Hanging,
		Shooting,
	};
}

