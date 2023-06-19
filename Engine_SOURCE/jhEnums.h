#pragma once

namespace jh::enums
{

	enum class eSceneType
	{
		Title,
		Play,
		Cave,
		Cave2,
		Jungle,
		End,
	};

	enum class eLayerType
	{
		None = 0,
		Camera,
		BackGround3,
		BackGround2,
		BackGround,
		Grid,
		Monster,
		MonsterObject,
		FriendsObject,
		Player,
		Friends,
		PlayerObject,
		BackGrouncObj,
		Effect,

		Particle,
		PostProcess,
		UI,
		End = 20,
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
		AudioListener,
		AudioSource,
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
		AudioClip,
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
		Fall,
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
		FlyDown,
		Eat,

		Hurt,
		Die,

		Event,

	};

	enum class eGeddyState
	{
		Idle,
		Hanging,
		Falling,
		Shooting,
	};
}

