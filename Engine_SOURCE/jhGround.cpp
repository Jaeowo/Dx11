#include "jhGround.h"
#include "jhCollider2D.h"

namespace jh
{
	Ground::Ground()
	{
		mCollider2D = this->AddComponent<Collider2D>();

	}
	Ground::~Ground()
	{
	}
	void Ground::Initalize()
	{
	}
	void Ground::Update()
	{
	}
	void Ground::FixedUpdate()
	{
	}
	void Ground::Render()
	{
	}
}