#include "jhButton.h"
#include "jhAnimator.h"
#include "jhResources.h"
#include "jhSpriteRenderer.h"
#include "jhButtonScript.h"
#include "jhTime.h"
#include "jhStoneDoor.h"
#include "jhObject.h"
#include "jhAudioClip.h"
#include "jhAudioSource.h"

namespace jh
{
	Button::Button()
		: mPosition(Vector3(0.0f, 0.0f, 0.0f))
		, mOneCount(false)
		, mTotalTime(0.0f)
		, mButtonState(eButtonState::Idle)
		, mPressTrigger(false)
		, mPressOneCheck(false)
	{
		mAnimator = AddComponent<Animator>();
		mTransform = GetComponent<Transform>();

		mTransform->SetPosition(mPosition);
		mTransform->SetScale(Vector3(0.3f,0.3f,1.0f));

		SpriteRenderer* horizontalsr = AddComponent<SpriteRenderer>();
		std::shared_ptr<Mesh> horizontalmesh = Resources::Find<Mesh>(L"RectMesh");
		std::shared_ptr<Material> horizontalmaterial = Resources::Find<Material>(L"Horizontalmaterial");
		horizontalsr->SetMaterial(horizontalmaterial);
		horizontalsr->SetMesh(horizontalmesh);

		Collider2D* mCollider = AddComponent<Collider2D>();
		mCollider->SetType(eColliderType::Rect);
		mCollider->SetSize(Vector2(0.2f, 0.1f));

		std::shared_ptr<Texture> HeavyButtontexture = Resources::Load<Texture>(L"Button", L"MapObject\\spr_HeavyButton_76x43.png");

		mAnimator->Create(L"Idle", HeavyButtontexture, Vector2(0.0f, 0.0f), Vector2(76.0f, 43.0f), Vector2::Zero, 1, 0.3f);
		mAnimator->Create(L"Press", HeavyButtontexture, Vector2(0.0f, 86.0f), Vector2(76.0f, 43.0f), Vector2::Zero, 3, 0.3f);
		mAnimator->Create(L"PressIdle", HeavyButtontexture, Vector2(0.0f, 129.0f), Vector2(76.0f, 43.0f), Vector2::Zero, 4, 0.3f);

		mAnimator->Play(L"Idle", false);

		mStonedoor = object::Instantiate<StoneDoor>(eLayerType::BackGround);
		mStonedoor->SetPosition(Vector3(-1.275f, 0.3f, 1.7f));
		mStonedoor->SetScale(Vector3(0.45f, 0.45f, 1.0f));
		mStonedoor->SetRotation(Vector3(0.0f, 0.0f, 270.0f));
		mStonedoor->SetCenter(Vector2(0.0f, -0.04f));

	}
	Button::~Button()
	{
	}
	void Button::Initalize()
	{
		GameObject::Initalize();
		AddComponent<ButtonScript>();
	}
	void Button::Update()
	{
		GameObject::Update();

		mCollider = GetComponent<Collider2D>();
		mTransform = GetComponent<Transform>();
		mTransform->SetPosition(mPosition);

		mTotalTime += Time::DeltaTime();

		if (mPressOneCheck == false)
		{
			if (mPressTrigger == true)
			{
				mButtonState = eButtonState::Press;
				mPressOneCheck = true;
			}
		}
		

		switch (mButtonState)
		{
		case jh::eButtonState::Idle:
			Idle();
			break;
		case jh::eButtonState::Press:
			Press();
			break;
		case jh::eButtonState::PressIdle:
			PressIdle();
			break;
		default:
			break;
		}

	}
	void Button::FixedUpdate()
	{
		GameObject::FixedUpdate();
	}
	void Button::Render()
	{
		GameObject::Render();
	}

	void Button::Idle()
	{
		if (mOneCount == false)
		{
			mAnimator->Play(L"Idle", false);

			mOneCount = true;
		}
	}

	void Button::Press()
	{
		if (mOneCount == false)
		{
			mAnimator->Play(L"Press", false);
			mTotalTime = 0.0f;

			std::shared_ptr<AudioClip> audioClip = Resources::Load<AudioClip>
				(L"press", L"..\\Resources\\Audio\\buttonLightPress.wav");

			AudioSource* audioSource = AddComponent<AudioSource>();
			audioSource->SetClip(audioClip);
			audioSource->SetLoop(false);


			audioSource->Play();
			mOneCount = true;

		}

		float newY = mCollider->GetCenter().y - Time::DeltaTime() * 0.1f; 
		mCollider->SetCenter(Vector2(0.0f, newY));

		if (newY <= -0.1f)
		{
			mOneCount = 0;
			mButtonState = eButtonState::PressIdle;
		}
	}

	void Button::PressIdle()
	{
		if (mOneCount == false)
		{
			mAnimator->Play(L"PressIdle", false);
			
			mStonedoor->SetOpenTrigger(true);
			mStonedoor->SetCount(false);
			RemoveComponent<Collider2D>();
			mOneCount = true;
			
		}
	}

	

}