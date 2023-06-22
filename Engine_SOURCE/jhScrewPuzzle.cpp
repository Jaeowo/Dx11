#include "jhScrewPuzzle.h"
#include "jhSpriteRenderer.h"
#include "jhResources.h"
#include "jhObject.h"
#include "jhAnimator.h"
#include "jhTime.h"
#include "jhScrewPuzzleScript.h"
#include "jhAudioClip.h"
#include "jhAudioSource.h"
namespace jh
{
	ScrewPuzzle::ScrewPuzzle()
		: mOneCount(false)
		, mTotalTime(0.0f)
		, mRotation(Vector3(0.0f, 0.0f, 0.0f))
		, mPosition(Vector3(0.0f, 0.0f, 0.0f))
		, mClearOn(false)
		, mPuzzleState(ePuzzleState::N1)
	{
		mAnimator = AddComponent<Animator>();
		mTransform = GetComponent<Transform>();

		Collider2D* mCollider = AddComponent<Collider2D>();
		mCollider->SetType(eColliderType::Rect);
		mCollider->SetSize(Vector2(0.2f, 0.1f));

		mTransform->SetScale(Vector3(0.3f, 0.3f, 1.0f));

		SpriteRenderer* gawksr = AddComponent<SpriteRenderer>();
		std::shared_ptr<Mesh> gawkmesh = Resources::Find<Mesh>(L"RectMesh");
		std::shared_ptr<Material> gawkmaterial = Resources::Find<Material>(L"GawkMaterial");
		gawksr->SetMaterial(gawkmaterial);
		gawksr->SetMesh(gawkmesh);

		std::shared_ptr<Texture> screwpuzzletexture1 = Resources::Load<Texture>
			(L"ScrewPuzzle1", L"MapObject\\sprScrewPuzzle2_69x38_strip5.png");

		std::shared_ptr<Texture> screwpuzzletexture2 = Resources::Load<Texture>
			(L"ScrewPuzzle2", L"MapObject\\sprScrewPuzzle3_69x38_strip5.png");

		std::shared_ptr<Texture> screwpuzzletexture3 = Resources::Load<Texture>
			(L"ScrewPuzzle3", L"MapObject\\sprScrewPuzzle4_69x38_strip5.png");

		mAnimator->Create(L"Puzzle1", screwpuzzletexture1, Vector2(0.0f, 0.0f), Vector2(69.0f, 38.0f), Vector2::Zero, 1, 0.2f);
		mAnimator->Create(L"Puzzle2", screwpuzzletexture1, Vector2(69.0f, 0.0f), Vector2(69.0f, 38.0f), Vector2::Zero, 1, 0.2f);
		mAnimator->Create(L"Puzzle3", screwpuzzletexture1, Vector2(138.0f, 0.0f), Vector2(69.0f, 38.0f), Vector2::Zero, 1, 0.2f);
		mAnimator->Create(L"Puzzle4", screwpuzzletexture1, Vector2(207.0f, 0.0f), Vector2(69.0f, 38.0f), Vector2::Zero, 1, 0.2f);
		mAnimator->Create(L"Puzzle5", screwpuzzletexture1, Vector2(276.0f, 0.0f), Vector2(69.0f, 38.0f), Vector2::Zero, 1, 0.2f);

		mAnimator->Create(L"Puzzle6", screwpuzzletexture2, Vector2(0.0f, 0.0f), Vector2(69.0f, 38.0f), Vector2::Zero, 1, 0.2f);
		mAnimator->Create(L"Puzzle7", screwpuzzletexture2, Vector2(69.0f, 0.0f), Vector2(69.0f, 38.0f), Vector2::Zero, 1, 0.2f);
		mAnimator->Create(L"Puzzle8", screwpuzzletexture2, Vector2(138.0f, 0.0f), Vector2(69.0f, 38.0f), Vector2::Zero, 1, 0.2f);
		mAnimator->Create(L"Puzzle9", screwpuzzletexture2, Vector2(207.0f, 0.0f), Vector2(69.0f, 38.0f), Vector2::Zero, 1, 0.2f);
		mAnimator->Create(L"Puzzle10", screwpuzzletexture2, Vector2(276.0f, 0.0f), Vector2(69.0f, 38.0f), Vector2::Zero, 1, 0.2f);

		mAnimator->Create(L"Puzzle11", screwpuzzletexture3, Vector2(0.0f, 0.0f), Vector2(69.0f, 38.0f), Vector2::Zero, 1, 0.2f);
		mAnimator->Create(L"Puzzle12", screwpuzzletexture3, Vector2(69.0f, 0.0f), Vector2(69.0f, 38.0f), Vector2::Zero, 1, 0.2f);
		mAnimator->Create(L"Puzzle13", screwpuzzletexture3, Vector2(138.0f, 0.0f), Vector2(69.0f, 38.0f), Vector2::Zero, 1, 0.2f);
		mAnimator->Create(L"Puzzle14", screwpuzzletexture3, Vector2(207.0f, 0.0f), Vector2(69.0f, 38.0f), Vector2::Zero, 1, 0.2f);
		mAnimator->Create(L"Puzzle15", screwpuzzletexture3, Vector2(276.0f, 0.0f), Vector2(69.0f, 38.0f), Vector2::Zero, 1, 0.2f);

		mAnimator->Play(L"Puzzle1", false);



	}
	ScrewPuzzle::~ScrewPuzzle()
	{
	}
	void ScrewPuzzle::Initalize()
	{
		GameObject::Initalize();
		AddComponent<ScrewPuzzleScript>();
	}
	void ScrewPuzzle::Update()
	{
		GameObject::Update();
		mAnimator = GetComponent<Animator>();
		mTransform = GetComponent<Transform>();
		mTransform->SetPosition(mPosition);

		mTransform->SetRotation(mRotation);

		mTotalTime += Time::DeltaTime();

		if (mPuzzleState == ePuzzleState::N4)
		{
			mClearOn = true;
		}
		else
		{
			mClearOn = false;
		}

		switch (mPuzzleState)
		{
		case jh::ePuzzleState::N1:
			N1();
			break;
		case jh::ePuzzleState::N2:
			N2();
			break;
		case jh::ePuzzleState::N3:
			N3();
			break;
		case jh::ePuzzleState::N4:
			N4();
			break;
		case jh::ePuzzleState::N5:
			N5();
			break;
		case jh::ePuzzleState::N6:
			N6();
			break;
		case jh::ePuzzleState::N7:
			N7();
			break;
		case jh::ePuzzleState::N8:
			N8();
			break;
		case jh::ePuzzleState::N9:
			N9();
			break;
		case jh::ePuzzleState::N10:
			N10();
			break;
		case jh::ePuzzleState::N11:
			N11();
			break;
		case jh::ePuzzleState::N12:
			N12();
			break;
		case jh::ePuzzleState::N13:
			N13();
			break;
		case jh::ePuzzleState::N14:
			N14();
			break;
		case jh::ePuzzleState::N15:
			N15();
			break;
		default:
			break;
		}
	}
	void ScrewPuzzle::FixedUpdate()
	{
		GameObject::FixedUpdate();
	}
	void ScrewPuzzle::Render()
	{
		GameObject::Render();
	}

	void ScrewPuzzle::N1()
	{
		if (mOneCount == false)
		{
		
			mAnimator->Play(L"Puzzle1", false);
			mOneCount = true;
		}
	}

	void ScrewPuzzle::N2()
	{
		if (mOneCount == false)
		{
			mAnimator->Play(L"Puzzle2", false);
			mOneCount = true;
		}
	}

	void ScrewPuzzle::N3()
	{
		if (mOneCount == false)
		{
			mAnimator->Play(L"Puzzle3", false);
			mOneCount = true;
		}
	}

	void ScrewPuzzle::N4()
	{
		if (mOneCount == false)
		{
			mAnimator->Play(L"Puzzle4", false);
			mOneCount = true;
		}
	}

	void ScrewPuzzle::N5()
	{
		if (mOneCount == false)
		{
			mAnimator->Play(L"Puzzle5", false);
			mOneCount = true;
		}
	}

	void ScrewPuzzle::N6()
	{
		if (mOneCount == false)
		{
			mAnimator->Play(L"Puzzle6", false);
			mOneCount = true;
		}
	}

	void ScrewPuzzle::N7()
	{
		if (mOneCount == false)
		{
			mAnimator->Play(L"Puzzle7", false);
			mOneCount = true;
		}
	}

	void ScrewPuzzle::N8()
	{
		if (mOneCount == false)
		{
			mAnimator->Play(L"Puzzle8", false);
			mOneCount = true;
		}
	}

	void ScrewPuzzle::N9()
	{
		if (mOneCount == false)
		{
			mAnimator->Play(L"Puzzle9", false);
			mOneCount = true;
		}
	}

	void ScrewPuzzle::N10()
	{
		if (mOneCount == false)
		{
			mAnimator->Play(L"Puzzle10", false);
			mOneCount = true;
		}
	}

	void ScrewPuzzle::N11()
	{
		if (mOneCount == false)
		{
			mAnimator->Play(L"Puzzle11", false);
			mOneCount = true;
		}
	}

	void ScrewPuzzle::N12()
	{
		if (mOneCount == false)
		{
			mAnimator->Play(L"Puzzle12", false);
			mOneCount = true;
		}
	}

	void ScrewPuzzle::N13()
	{
		if (mOneCount == false)
		{
			mAnimator->Play(L"Puzzle13", false);
			mOneCount = true;
		}
	}

	void ScrewPuzzle::N14()
	{
		if (mOneCount == false)
		{
			mAnimator->Play(L"Puzzle14", false);
			mOneCount = true;
		}
	}

	void ScrewPuzzle::N15()
	{
		if (mOneCount == false)
		{
			mAnimator->Play(L"Puzzle15", false);
			mOneCount = true;
		}
	}

	void ScrewPuzzle::IncrementState()
	{
		switch (mPuzzleState)
		{
		case ePuzzleState::N1:  mPuzzleState = ePuzzleState::N2; break;
		case ePuzzleState::N2:  mPuzzleState = ePuzzleState::N3; break;
		case ePuzzleState::N3:  mPuzzleState = ePuzzleState::N4; break;
		case ePuzzleState::N4:  mPuzzleState = ePuzzleState::N5; break;
		case ePuzzleState::N5:  mPuzzleState = ePuzzleState::N6; break;
		case ePuzzleState::N6:  mPuzzleState = ePuzzleState::N7; break;
		case ePuzzleState::N7:  mPuzzleState = ePuzzleState::N8; break;
		case ePuzzleState::N8:  mPuzzleState = ePuzzleState::N9; break;
		case ePuzzleState::N9:  mPuzzleState = ePuzzleState::N10; break;
		case ePuzzleState::N10:  mPuzzleState = ePuzzleState::N11; break;
		case ePuzzleState::N11:  mPuzzleState = ePuzzleState::N12; break;
		case ePuzzleState::N12:  mPuzzleState = ePuzzleState::N13; break;
		case ePuzzleState::N13:  mPuzzleState = ePuzzleState::N14; break;
		case ePuzzleState::N14:  mPuzzleState = ePuzzleState::N15; break;
		case ePuzzleState::N15: mPuzzleState = ePuzzleState::N1; break; 
		default: break;
		}
		mOneCount = false;
	}



}