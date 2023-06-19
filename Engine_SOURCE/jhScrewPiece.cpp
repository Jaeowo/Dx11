#include "jhScrewPiece.h"
#include "jhSpriteRenderer.h"
#include "jhResources.h"
#include "jhObject.h"
#include "jhAnimator.h"
#include "jhTime.h"

namespace jh
{
	ScrewPiece::ScrewPiece()
		: mOneCount(false)
		, mTotalTime(0.0f)
		, mRotation(Vector3(0.0f, 0.0f, 0.0f))
		, mPosition(Vector3(0.0f, 0.0f, 0.0f))
	{
		mAnimator = AddComponent<Animator>();
		mTransform = GetComponent<Transform>();

		mTransform->SetScale(Vector3(0.32f, 0.32f, 1.0f));

		SpriteRenderer* gawksr = AddComponent<SpriteRenderer>();
		std::shared_ptr<Mesh> gawkmesh = Resources::Find<Mesh>(L"RectMesh");
		std::shared_ptr<Material> gawkmaterial = Resources::Find<Material>(L"GawkMaterial");
		gawksr->SetMaterial(gawkmaterial);
		gawksr->SetMesh(gawkmesh);

		std::shared_ptr<Texture> puzzlepiecetexture = Resources::Load<Texture>(L"PuzzlePiece", L"MapObject\\screwPuzzlePiece.png");

		mAnimator->Create(L"Piece", puzzlepiecetexture, Vector2(0.0f, 0.0f), Vector2(35.0f, 178.0f), Vector2::Zero, 1, 0.2f);

		mAnimator->Play(L"Piece", false);


	}
	ScrewPiece::~ScrewPiece()
	{
	}
	void ScrewPiece::Initalize()
	{
		GameObject::Initalize();
	}
	void ScrewPiece::Update()
	{
		GameObject::Update();
		mAnimator = GetComponent<Animator>();
		mTransform = GetComponent<Transform>();
		mTransform->SetPosition(mPosition);

		mTransform->SetRotation(mRotation);

		mTotalTime += Time::DeltaTime();

		
	}
	void ScrewPiece::FixedUpdate()
	{
		GameObject::FixedUpdate();
	}
	void ScrewPiece::Render()
	{
		GameObject::Render();
	}



}