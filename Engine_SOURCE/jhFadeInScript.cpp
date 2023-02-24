#include "jhFadeInScript.h"
#include "jhConstantBuffer.h"
#include "jhApplication.h"
#include "jhRenderer.h"
#include "jhTime.h"
#include "jhInput.h"
extern jh::Application application;

namespace jh
{
	FadeInScript::FadeInScript()
		: Script()
		, mAmount(0.0f)
	{
	}
	FadeInScript::~FadeInScript()
	{
	}
	void FadeInScript::Initalize()
	{
		
	}
	void FadeInScript::Update()
	{

		ConstantBuffer* cb = renderer::constantBuffers[(UINT)eCBType::Fade];
		renderer::FadeCB data;

		if (Input::GetKeyState(eKeyCode::F) == eKeyState::PRESSED)
		{
			mAmount += Time::DeltaTime();
			data.FadeAmount = mAmount;
		}
		if (mAmount >= 1.0f)
		{
			mAmount = 1.0f;
			data.FadeAmount = mAmount;
		}
	
		cb->Bind(&data);
		cb->SetPipline(eShaderStage::VS);
		cb->SetPipline(eShaderStage::PS);

	}
	void FadeInScript::FixedUpdate()
	{
	}
	void FadeInScript::Render()
	{
	}
}