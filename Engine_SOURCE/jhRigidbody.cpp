#include "jhRigidbody.h"
#include "jhTime.h"
#include "jhGameObject.h"

namespace jh
{

	Rigidbody::Rigidbody()
		: Component(eComponentType::Rigidbody)
		, mMass(1.0f)
		, mFriction(100.0f)
	{
		mLimitVelocity.x = 200.f;
		mLimitVelocity.y = 1000.f;
		mbGround = false;
		mGravity = Vector3(0.0f, 800.0f, 0.0f);
	}
	Rigidbody::~Rigidbody()
	{
	}
	void Rigidbody::Initalize()
	{
	}
	void Rigidbody::Update()
	{
		//�̵�
		// F = M x A
		// A = F / M
		mAccelation = mForce / mMass;

		// �ӵ��� ���ӵ��� ���Ѵ�
		mVelocity += mAccelation * Time::DeltaTime();

		if (mbGround)
		{
			// ������ ������
			Vector3 gravity = mGravity;
			gravity.Normalize();
			float dot = (mVelocity.x * gravity.x + mVelocity.y + gravity.y);
			mVelocity -= gravity * dot;
		}
	
		else
		{
			// ���߿� ���� ��
			mVelocity += mGravity * Time::DeltaTime();
		}

		// �ִ� �ӵ� ����
		Vector3 gravity = mGravity;
		gravity.Normalize();
		float dot = (mVelocity.x * gravity.x + mVelocity.y + gravity.y);
		gravity = gravity * dot;

		Vector3 sideVelocity = mVelocity - gravity;
		if (mLimitVelocity.y < gravity.Length())
		{
			gravity.Normalize();
			gravity *= mLimitVelocity.y;
		}
		
		if (mLimitVelocity.x < sideVelocity.Length())
		{
			sideVelocity.Normalize();
			sideVelocity *= mLimitVelocity.x;
		}
		mVelocity = gravity + sideVelocity;

		//������ ���� ( ����� ���� ����, �ӵ��� 0 �� �ƴ� ��)
		//if (!(mVelocity == Vector3::Zero))
		//{
		//	// �ӵ��� �ݴ� �������� �������� ����
		//	Vector3 friction = -mVelocity;
		//	//friction = friction.Normalize() * mFriction * mMass * Time::DeltaTime();


		//	// ���������� ���� �ӵ� ���ҷ��� ���� �ӵ����� �� ū ���
		//	if (mVelocity.Length() < friction.Length())
		//	{
		//		// �ӵ��� 0 �� �����.
		//		mVelocity = Vector3(0.f, 0.f, 0.f);
		//	}
		//	else
		//	{
		//		// �ӵ����� ���������� ���� �ݴ�������� �ӵ��� �����Ѵ�.
		//		mVelocity += friction;
		//	}
		//}


		// �ӵ��� �°� ��ü�� �̵���Ų��.
		Vector3 pos = GetOwner()->GetPos();
		pos = pos + mVelocity * Time::DeltaTime();
		GetOwner()->SetPos(pos);
		mForce = (Vector3(0.f, 0.f, 0.f));
	}
	void Rigidbody::FixedUpdate()
	{
	}
	void Rigidbody::Render()
	{
	}
	void Rigidbody::AddForce(Vector3 force)
	{
		mForce += force;
	}
}