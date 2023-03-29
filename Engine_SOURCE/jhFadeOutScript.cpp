#include "jhFadeOutScript.h"
#include "jhConstantBuffer.h"
#include "jhApplication.h"
#include "jhRenderer.h"
#include "jhTime.h"
#include "jhInput.h"

namespace jh
{
	FadeOutScript::FadeOutScript()
		: Script()
		, mAmount(1.0f)
	{
	}
	FadeOutScript::~FadeOutScript()
	{
	}
	void FadeOutScript::Initalize()
	{
	}
	void FadeOutScript::Update()
	{
		ConstantBuffer* cb = renderer::constantBuffers[(UINT)eCBType::Fade];
		renderer::FadeCB data;

		data.FadeAmount = mAmount;

		if (Input::GetKeyState(eKeyCode::Z) == eKeyState::PRESSED)
		{
			mAmount -= Time::DeltaTime();
			data.FadeAmount = mAmount;
		}
		if (mAmount <= 0.0f)
		{
			mAmount = 0.0f;
			data.FadeAmount = mAmount;
		}

		cb->SetData(&data);
		cb->Bind(eShaderStage::VS);
		cb->Bind(eShaderStage::PS);
	}
	void FadeOutScript::FixedUpdate()
	{
	}
	void FadeOutScript::Render()
	{
	}
}