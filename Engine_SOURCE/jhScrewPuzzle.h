#pragma once
#include "jhGameObject.h"

namespace jh
{
	class Transform;
	class Animator;

	enum class ePuzzleState
	{
		N1,
		N2,
		N3,
		N4,
		N5,
		N6,
		N7,
		N8,
		N9,
		N10,
		N11,
		N12,
		N13,
		N14,
		N15
	};

	class ScrewPuzzle
		: public GameObject
	{
	public:
		ScrewPuzzle();
		virtual ~ScrewPuzzle();

		virtual void Initalize();
		virtual void Update();
		virtual void FixedUpdate();
		virtual void Render();

		void SetPosition(Vector3 position) { mPosition = position; }
		void SetCount(bool onecount) { mOneCount = onecount; }

		void SetPuzzleState(ePuzzleState puzzlestate) { mPuzzleState = puzzlestate; }

		bool GetClear() { return mClearOn; }

		void N1();
		void N2();
		void N3();
		void N4();
		void N5();
		void N6();
		void N7();
		void N8();
		void N9();
		void N10();
		void N11();
		void N12();
		void N13();
		void N14();
		void N15();

		void IncrementState();

	private:
		Vector3 mPosition;
		Vector3 mTargetPosition;
		Transform* mTransform;
		Animator* mAnimator;
		Vector3 mRotation;

		ePuzzleState mPuzzleState;

		bool mOneCount;
		bool mClearOn;
		float mTotalTime;
	};
}