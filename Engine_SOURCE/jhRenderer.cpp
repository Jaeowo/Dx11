#include "jhRenderer.h"
#include "jhResources.h"
#include "jhMaterial.h"
#include "jhSceneManager.h"
#include "jhPaintShader.h"
#include "jhParticleShader.h"
#include "jhTime.h"

namespace jh::renderer
{

	Vertex vertexes[4] = {};
	ConstantBuffer* constantBuffers[(UINT)eCBType::End] = {};
	Microsoft::WRL::ComPtr<ID3D11SamplerState> samplerStates[(UINT)eSamplerType::End] = {};
	Microsoft::WRL::ComPtr<ID3D11RasterizerState> rasterizerStates[(UINT)eRSType::End] = {};
	Microsoft::WRL::ComPtr<ID3D11DepthStencilState> depthstencilStates[(UINT)eDSType::End] = {};
	Microsoft::WRL::ComPtr<ID3D11BlendState> blendStates[(UINT)eBSType::End] = {};

	Camera* mainCamera = nullptr;
	std::vector<Camera*> cameras[(UINT)eSceneType::End];
	std::vector<DebugMesh> debugMeshes;
	std::vector<LightAttribute> lights;
	StructedBuffer* lightsBuffer = nullptr;

	std::shared_ptr<Texture> postProcessTexture = nullptr;

	void LoadMesh()
	{
#pragma region POINT MESH
		Vertex v = {};
		std::shared_ptr<Mesh> pointMesh = std::make_shared<Mesh>();
		Resources::Insert<Mesh>(L"PointMesh", pointMesh);
		pointMesh->CreateVertexBuffer(&v, 1);
		UINT pointIndex = 0;
		pointMesh->CreateIndexBuffer(&pointIndex, 1);
#pragma endregion
#pragma region RECT MESH
		//RECT
		vertexes[0].pos = Vector4(-0.5f, 0.5f, 0.0f, 1.0f);
		vertexes[0].color = Vector4(0.f, 1.f, 0.f, 1.f);
		vertexes[0].uv = Vector2(0.f, 0.f);

		vertexes[1].pos = Vector4(0.5f, 0.5f, 0.0f, 1.0f);
		vertexes[1].color = Vector4(1.f, 1.f, 1.f, 1.f);
		vertexes[1].uv = Vector2(1.0f, 0.0f);

		vertexes[2].pos = Vector4(0.5f, -0.5f, 0.0f, 1.0f);
		vertexes[2].color = Vector4(1.f, 0.f, 0.f, 1.f);
		vertexes[2].uv = Vector2(1.0f, 1.0f);

		vertexes[3].pos = Vector4(-0.5f, -0.5f, 0.0f, 1.0f);
		vertexes[3].color = Vector4(0.f, 0.f, 1.f, 1.f);
		vertexes[3].uv = Vector2(0.0f, 1.0f);

		// Crate Mesh
		std::shared_ptr<Mesh> mesh = std::make_shared<Mesh>();
		Resources::Insert<Mesh>(L"RectMesh", mesh);
		mesh->CreateVertexBuffer(vertexes, 4);

		std::vector<UINT> indexes;
		indexes.push_back(0);
		indexes.push_back(1);
		indexes.push_back(2);
		indexes.push_back(0);
		indexes.push_back(2);
		indexes.push_back(3);
		indexes.push_back(0);
		mesh->CreateIndexBuffer(indexes.data(), indexes.size());
#pragma endregion
#pragma region DEBUG RECTMESH
		vertexes[0].pos = Vector4(-0.5f, 0.5f, -0.00001f, 1.0f);
		vertexes[0].color = Vector4(0.f, 1.f, 0.f, 1.f);
		vertexes[0].uv = Vector2(0.f, 0.f);

		vertexes[1].pos = Vector4(0.5f, 0.5f, -0.00001, 1.0f);
		vertexes[1].color = Vector4(1.f, 1.f, 1.f, 1.f);
		vertexes[1].uv = Vector2(1.0f, 0.0f);

		vertexes[2].pos = Vector4(0.5f, -0.5f, -0.00001, 1.0f);
		vertexes[2].color = Vector4(1.f, 0.f, 0.f, 1.f);
		vertexes[2].uv = Vector2(1.0f, 1.0f);

		vertexes[3].pos = Vector4(-0.5f, -0.5f, -0.00001, 1.0f);
		vertexes[3].color = Vector4(0.f, 0.f, 1.f, 1.f);
		vertexes[3].uv = Vector2(0.0f, 1.0f);

		// Crate Mesh
		std::shared_ptr<Mesh> debugmesh = std::make_shared<Mesh>();
		Resources::Insert<Mesh>(L"DebugRectMesh", debugmesh);
		debugmesh->CreateVertexBuffer(vertexes, 4);
		debugmesh->CreateIndexBuffer(indexes.data(), indexes.size());
#pragma endregion
#pragma region CIRCLE MESH
		std::vector<Vertex> circleVtxes;
		Vertex center = {};
		center.pos = Vector4(0.0f, 0.0f, -0.00001f, 1.0f);
		center.color = Vector4(0.0f, 1.0f, 0.0f, 1.0f);
		center.uv = Vector2::Zero;

		circleVtxes.push_back(center);

		int iSlice = 80;
		float fRadius = 0.5f;
		float fTheta = XM_2PI / (float)iSlice;


		for (size_t i = 0; i < iSlice; i++)
		{
			Vertex vtx = {};
			vtx.pos = Vector4
			(
				fRadius * cosf(fTheta * (float)i)
				, fRadius * sinf(fTheta * (float)i)
				, -0.00001f, 1.0f
			);
			vtx.color = center.color;

			circleVtxes.push_back(vtx);
		}
		indexes.clear();
		for (size_t i = 0; i < iSlice - 2; i++)
		{
			indexes.push_back(i + 1);
		}
		indexes.push_back(1);

		// Crate Mesh
		std::shared_ptr<Mesh> cirlceMesh = std::make_shared<Mesh>();
		Resources::Insert<Mesh>(L"CircleMesh", cirlceMesh);
		cirlceMesh->CreateVertexBuffer(circleVtxes.data(), circleVtxes.size());
		cirlceMesh->CreateIndexBuffer(indexes.data(), indexes.size());
#pragma endregion
	}

	void LoadShader()
	{
#pragma region DEFAULT TRIANGLE SHADER
		std::shared_ptr<Shader> shader = std::make_shared<Shader>();
		shader->Create(eShaderStage::VS, L"TriangleVS.hlsl", "main");
		shader->Create(eShaderStage::PS, L"TrianglePS.hlsl", "main");
		Resources::Insert<Shader>(L"RectShader", shader);
#pragma endregion
#pragma region SPRITE SHADER
		std::shared_ptr<Shader> spriteShader = std::make_shared<Shader>();
		spriteShader->Create(eShaderStage::VS, L"SpriteVS.hlsl", "main");
		spriteShader->Create(eShaderStage::PS, L"SpritePS.hlsl", "main");
		spriteShader->SetRSState(eRSType::SolidNone);
		Resources::Insert<Shader>(L"SpriteShader", spriteShader);
#pragma endregion
#pragma region UI SHADER
		std::shared_ptr<Shader> uiShader = std::make_shared<Shader>();
		uiShader->Create(eShaderStage::VS, L"UserInterfaceVS.hlsl", "main");
		uiShader->Create(eShaderStage::PS, L"UserInterfacePS.hlsl", "main");

		Resources::Insert<Shader>(L"UIShader", uiShader);
#pragma endregion
#pragma region GRID SHADER
		std::shared_ptr<Shader> gridShader = std::make_shared<Shader>();
		gridShader->Create(eShaderStage::VS, L"GridVS.hlsl", "main");
		gridShader->Create(eShaderStage::PS, L"GridPS.hlsl", "main");
		gridShader->SetRSState(eRSType::SolidNone);
		gridShader->SetDSState(eDSType::NoWrite);
		gridShader->SetBSState(eBSType::AlphaBlend);

		Resources::Insert<Shader>(L"GridShader", gridShader);
#pragma endregion
#pragma region FADE SHADER
		std::shared_ptr<Shader> fadeInShader = std::make_shared<Shader>();
		fadeInShader->Create(eShaderStage::VS, L"FadeInVS.hlsl", "main");
		fadeInShader->Create(eShaderStage::PS, L"FadeInPS.hlsl", "main");

		Resources::Insert<Shader>(L"FadeInShader", fadeInShader);
#pragma endregion
#pragma region DEBUG SHADER
		std::shared_ptr<Shader> debugShader = std::make_shared<Shader>();
		debugShader->Create(eShaderStage::VS, L"DebugVS.hlsl", "main");
		debugShader->Create(eShaderStage::PS, L"DebugPS.hlsl", "main");
		debugShader->SetRSState(eRSType::SolidNone);
		debugShader->SetDSState(eDSType::NoWrite);
		debugShader->SetBSState(eBSType::AlphaBlend);
		debugShader->SetTopology(D3D11_PRIMITIVE_TOPOLOGY::D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP);

		Resources::Insert<Shader>(L"DebugShader", debugShader);
#pragma endregion
#pragma region PAINT SHADER
		std::shared_ptr<PaintShader> paintShader = std::make_shared<PaintShader>();
		paintShader->Create(L"PaintCS.hlsl", "main");
		Resources::Insert<PaintShader>(L"PaintShader", paintShader);
#pragma endregion
#pragma region PARTICLE SHADER
		std::shared_ptr<Shader> particleShader = std::make_shared<Shader>();
		particleShader->Create(eShaderStage::VS, L"ParticleVS.hlsl", "main");
		particleShader->Create(eShaderStage::GS, L"ParticleGS.hlsl", "main");
		particleShader->Create(eShaderStage::PS, L"ParticlePS.hlsl", "main");
		particleShader->SetRSState(eRSType::SolidNone);
		particleShader->SetDSState(eDSType::NoWrite);
		particleShader->SetBSState(eBSType::AlphaBlend);
		particleShader->SetTopology(D3D11_PRIMITIVE_TOPOLOGY::D3D11_PRIMITIVE_TOPOLOGY_POINTLIST);
		Resources::Insert<Shader>(L"ParticleShader", particleShader);

		std::shared_ptr<ParticleShader> particleCS = std::make_shared<ParticleShader>();
		Resources::Insert<ParticleShader>(L"ParticleCS", particleCS);
		particleCS->Create(L"ParticleCS.hlsl", "main");
#pragma endregion
#pragma region POST PROCESS SHADER
		std::shared_ptr<Shader> postProcessShader = std::make_shared<Shader>();
		postProcessShader->Create(eShaderStage::VS, L"PostProcessVS.hlsl", "main");
		postProcessShader->Create(eShaderStage::PS, L"PostProcessPS.hlsl", "main");
		postProcessShader->SetDSState(eDSType::NoWrite);
		Resources::Insert<Shader>(L"PostProcessShader", postProcessShader);
#pragma endregion
	}

	void SetUpState()
	{
#pragma region Input layout
		D3D11_INPUT_ELEMENT_DESC arrLayoutDesc[3] = {};

		arrLayoutDesc[0].AlignedByteOffset = 0;
		arrLayoutDesc[0].Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
		arrLayoutDesc[0].InputSlot = 0;
		arrLayoutDesc[0].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
		arrLayoutDesc[0].SemanticName = "POSITION";
		arrLayoutDesc[0].SemanticIndex = 0;

		arrLayoutDesc[1].AlignedByteOffset = 16;
		arrLayoutDesc[1].Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
		arrLayoutDesc[1].InputSlot = 0;
		arrLayoutDesc[1].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
		arrLayoutDesc[1].SemanticName = "COLOR";
		arrLayoutDesc[1].SemanticIndex = 0;

		arrLayoutDesc[2].AlignedByteOffset = 32;
		arrLayoutDesc[2].Format = DXGI_FORMAT_R32G32_FLOAT;
		arrLayoutDesc[2].InputSlot = 0;
		arrLayoutDesc[2].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
		arrLayoutDesc[2].SemanticName = "TEXCOORD";
		arrLayoutDesc[2].SemanticIndex = 0;


		std::shared_ptr<Shader> shader = Resources::Find<Shader>(L"RectShader");
		GetDevice()->CreateInputLayout(arrLayoutDesc, 3
			, shader->GetVSBlobBufferPointer()
			, shader->GetVSBlobBufferSize()
			, shader->GetInputLayoutAddressOf());

		std::shared_ptr<Shader> spriteShader = Resources::Find<Shader>(L"SpriteShader");
		GetDevice()->CreateInputLayout(arrLayoutDesc, 3
			, spriteShader->GetVSBlobBufferPointer()
			, spriteShader->GetVSBlobBufferSize()
			, spriteShader->GetInputLayoutAddressOf());


		std::shared_ptr<Shader> uiShader = Resources::Find<Shader>(L"UIShader");
		GetDevice()->CreateInputLayout(arrLayoutDesc, 3
			, uiShader->GetVSBlobBufferPointer()
			, uiShader->GetVSBlobBufferSize()
			, uiShader->GetInputLayoutAddressOf());

		std::shared_ptr<Shader> gridShader = Resources::Find<Shader>(L"GridShader");
		GetDevice()->CreateInputLayout(arrLayoutDesc, 3
			, gridShader->GetVSBlobBufferPointer()
			, gridShader->GetVSBlobBufferSize()
			, gridShader->GetInputLayoutAddressOf());

		std::shared_ptr<Shader> FadeInShader = Resources::Find<Shader>(L"FadeInShader");
		GetDevice()->CreateInputLayout(arrLayoutDesc, 3
			, FadeInShader->GetVSBlobBufferPointer()
			, FadeInShader->GetVSBlobBufferSize()
			, FadeInShader->GetInputLayoutAddressOf());

		std::shared_ptr<Shader> debugShader = Resources::Find<Shader>(L"DebugShader");
		GetDevice()->CreateInputLayout(arrLayoutDesc, 3
			, debugShader->GetVSBlobBufferPointer()
			, debugShader->GetVSBlobBufferSize()
			, debugShader->GetInputLayoutAddressOf());

		std::shared_ptr<Shader> particleShader = Resources::Find<Shader>(L"ParticleShader");
		GetDevice()->CreateInputLayout(arrLayoutDesc, 3
			, particleShader->GetVSBlobBufferPointer()
			, particleShader->GetVSBlobBufferSize()
			, particleShader->GetInputLayoutAddressOf());


		std::shared_ptr<Shader> postProcessShader = Resources::Find<Shader>(L"PostProcessShader");
		GetDevice()->CreateInputLayout(arrLayoutDesc, 3
			, postProcessShader->GetVSBlobBufferPointer()
			, postProcessShader->GetVSBlobBufferSize()
			, postProcessShader->GetInputLayoutAddressOf());
#pragma endregion
#pragma region sampler state
		D3D11_SAMPLER_DESC samplerDesc = {};
		samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_WRAP;
		samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_WRAP;
		samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_WRAP;
		//D3D11_FILTER_MIN_POINT_MAG_MIP_LINEAR = 0x5,
		//D3D11_FILTER_MIN_LINEAR_MAG_MIP_POINT = 0x10,
		samplerDesc.Filter = D3D11_FILTER::D3D11_FILTER_MIN_LINEAR_MAG_MIP_POINT;


		GetDevice()->CreateSamplerState
		(
			&samplerDesc
			, samplerStates[(UINT)eSamplerType::Point].GetAddressOf()
		);

		samplerDesc.Filter = D3D11_FILTER::D3D11_FILTER_MIN_POINT_MAG_MIP_LINEAR;
		GetDevice()->CreateSamplerState
		(
			&samplerDesc
			, samplerStates[(UINT)eSamplerType::Linear].GetAddressOf()
		);

		samplerDesc.Filter = D3D11_FILTER::D3D11_FILTER_ANISOTROPIC;
		GetDevice()->CreateSamplerState
		(
			&samplerDesc
			, samplerStates[(UINT)eSamplerType::Anisotropic].GetAddressOf()
		);

		GetDevice()->BindsSamplers((UINT)eSamplerType::Point
			, 1, samplerStates[(UINT)eSamplerType::Point].GetAddressOf());

		GetDevice()->BindsSamplers((UINT)eSamplerType::Linear
			, 1, samplerStates[(UINT)eSamplerType::Linear].GetAddressOf());

		GetDevice()->BindsSamplers((UINT)eSamplerType::Anisotropic
			, 1, samplerStates[(UINT)eSamplerType::Anisotropic].GetAddressOf());
#pragma endregion
#pragma region Rasterizer state
		D3D11_RASTERIZER_DESC rsDesc = {};
		rsDesc.FillMode = D3D11_FILL_MODE::D3D11_FILL_SOLID;
		rsDesc.CullMode = D3D11_CULL_MODE::D3D11_CULL_BACK;

		GetDevice()->CreateRasterizerState(&rsDesc
			, rasterizerStates[(UINT)eRSType::SolidBack].GetAddressOf());

		rsDesc.FillMode = D3D11_FILL_MODE::D3D11_FILL_SOLID;
		rsDesc.CullMode = D3D11_CULL_MODE::D3D11_CULL_FRONT;

		GetDevice()->CreateRasterizerState(&rsDesc
			, rasterizerStates[(UINT)eRSType::SolidFront].GetAddressOf());

		rsDesc.FillMode = D3D11_FILL_MODE::D3D11_FILL_SOLID;
		rsDesc.CullMode = D3D11_CULL_MODE::D3D11_CULL_NONE;

		GetDevice()->CreateRasterizerState(&rsDesc
			, rasterizerStates[(UINT)eRSType::SolidNone].GetAddressOf());

		rsDesc.FillMode = D3D11_FILL_MODE::D3D11_FILL_WIREFRAME;
		rsDesc.CullMode = D3D11_CULL_MODE::D3D11_CULL_NONE;

		GetDevice()->CreateRasterizerState(&rsDesc
			, rasterizerStates[(UINT)eRSType::WireframeNone].GetAddressOf());


#pragma endregion
#pragma region Depth Stencil State
		D3D11_DEPTH_STENCIL_DESC dsDesc = {};
		dsDesc.DepthEnable = true;
		dsDesc.DepthFunc = D3D11_COMPARISON_FUNC::D3D11_COMPARISON_LESS_EQUAL;
		dsDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK::D3D11_DEPTH_WRITE_MASK_ALL;
		dsDesc.StencilEnable = false;

		GetDevice()->CreateDepthStencilState(&dsDesc
			, depthstencilStates[(UINT)eDSType::Less].GetAddressOf());

		dsDesc.DepthEnable = true;
		dsDesc.DepthFunc = D3D11_COMPARISON_FUNC::D3D11_COMPARISON_GREATER;
		dsDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK::D3D11_DEPTH_WRITE_MASK_ALL;
		dsDesc.StencilEnable = false;

		GetDevice()->CreateDepthStencilState(&dsDesc
			, depthstencilStates[(UINT)eDSType::Greater].GetAddressOf());

		dsDesc.DepthEnable = true;
		dsDesc.DepthFunc = D3D11_COMPARISON_FUNC::D3D11_COMPARISON_LESS;
		dsDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK::D3D11_DEPTH_WRITE_MASK_ZERO;
		dsDesc.StencilEnable = false;

		GetDevice()->CreateDepthStencilState(&dsDesc
			, depthstencilStates[(UINT)eDSType::NoWrite].GetAddressOf());

		dsDesc.DepthEnable = false;
		dsDesc.DepthFunc = D3D11_COMPARISON_FUNC::D3D11_COMPARISON_LESS;
		dsDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK::D3D11_DEPTH_WRITE_MASK_ZERO;
		dsDesc.StencilEnable = false;

		GetDevice()->CreateDepthStencilState(&dsDesc
			, depthstencilStates[(UINT)eDSType::None].GetAddressOf());

#pragma endregion
#pragma region Blend State

		blendStates[(UINT)eBSType::Default] = nullptr;

		D3D11_BLEND_DESC bsDesc = {};
		bsDesc.AlphaToCoverageEnable = false;
		bsDesc.IndependentBlendEnable = false;
		bsDesc.RenderTarget[0].BlendEnable = true;
		bsDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP::D3D11_BLEND_OP_ADD;
		bsDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
		bsDesc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
		bsDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP::D3D11_BLEND_OP_ADD;
		bsDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
		bsDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;

		bsDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

		GetDevice()->CreateBlendState(&bsDesc, blendStates[(UINT)eBSType::AlphaBlend].GetAddressOf());

		bsDesc.AlphaToCoverageEnable = false;
		bsDesc.IndependentBlendEnable = false;

		bsDesc.RenderTarget[0].BlendEnable = true;
		bsDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP::D3D11_BLEND_OP_ADD;
		bsDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_ONE;
		bsDesc.RenderTarget[0].DestBlend = D3D11_BLEND_ONE;
		bsDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

		GetDevice()->CreateBlendState(&bsDesc, blendStates[(UINT)eBSType::OneOne].GetAddressOf());

#pragma endregion
	}

	void LoadBuffer()
	{
		#pragma region CONSTANT BUFFER
		constantBuffers[(UINT)eCBType::Transform] = new ConstantBuffer(eCBType::Transform);
		constantBuffers[(UINT)eCBType::Transform]->Create(sizeof(TransformCB));

		constantBuffers[(UINT)eCBType::Material] = new ConstantBuffer(eCBType::Material);
		constantBuffers[(UINT)eCBType::Material]->Create(sizeof(MaterialCB));

		constantBuffers[(UINT)eCBType::Grid] = new ConstantBuffer(eCBType::Grid);
		constantBuffers[(UINT)eCBType::Grid]->Create(sizeof(GridCB));

		constantBuffers[(UINT)eCBType::Fade] = new ConstantBuffer(eCBType::Fade);
		constantBuffers[(UINT)eCBType::Fade]->Create(sizeof(FadeCB));

		constantBuffers[(UINT)eCBType::Animation] = new ConstantBuffer(eCBType::Animation);
		constantBuffers[(UINT)eCBType::Animation]->Create(sizeof(AnimationCB));

		constantBuffers[(UINT)eCBType::Light] = new ConstantBuffer(eCBType::Light);
		constantBuffers[(UINT)eCBType::Light]->Create(sizeof(LightCB));

		constantBuffers[(UINT)eCBType::ParticleSystem] = new ConstantBuffer(eCBType::ParticleSystem);
		constantBuffers[(UINT)eCBType::ParticleSystem]->Create(sizeof(ParticleSystemCB));

		constantBuffers[(UINT)eCBType::Noise] = new ConstantBuffer(eCBType::Noise);
		constantBuffers[(UINT)eCBType::Noise]->Create(sizeof(NoiseCB));
#pragma endregion
		#pragma region STRUCTED BUFFER
		//Structed buffer
		lightsBuffer = new StructedBuffer();
		lightsBuffer->Create(sizeof(LightAttribute), 128, eSRVType::SRV, nullptr, true);
#pragma endregion
	}

	void LoadTexture()
	{
#pragma region STUDY TEXTURE
		//수업 진도용임 . 나중에 삭제 하면 됨
		Resources::Load<Texture>(L"SmileTexture", L"Smile.png");
		Resources::Load<Texture>(L"DefaultSprite", L"Light.png");
		//Resources::Load<Texture>(L"HPBarTexture", L"HPBar.png");
		Resources::Load<Texture>(L"noise_01", L"noise\\noise_01.png");

		//noise
		postProcessTexture = std::make_shared<Texture>();
		postProcessTexture->Create(1600, 900, DXGI_FORMAT_R8G8B8A8_UNORM, D3D11_BIND_SHADER_RESOURCE);
		postProcessTexture->BindShaderResource(eShaderStage::PS, 60);
#pragma endregion
#pragma region TITLESCENE TEXTURE
		Resources::Load<Texture>(L"TitleSkyTexture", L"TitleSky.png");
		Resources::Load<Texture>(L"OwlboyLogoTexture", L"OwlboyLogo.png");
		Resources::Load<Texture>(L"TitleRightTexture", L"TitleRight.png");
		Resources::Load<Texture>(L"TitleLeftTexture", L"TitleLeft.png");
		Resources::Load<Texture>(L"LeftOtusTexture", L"Title Screen\\sprOtus_245x137_strip6.png");
		Resources::Load<Texture>(L"GrassHillTexture", L"Title Screen\\sprGrasshillBottom_400x600.png");
		Resources::Load<Texture>(L"GrassPathwayTexture", L"Title Screen\\sprGrassPathway_340x170.png");
#pragma endregion
#pragma region BACKGROUND TEXTURE
		Resources::Load<Texture>(L"BackSkyTexture", L"BackSky.png");
		Resources::Load<Texture>(L"HpBarTexture", L"HpBar.png");
		Resources::Load<Texture>(L"TileFloorTexture", L"Vellie-Tropos-Owl Temple assets\\island01.png");
		Resources::Load<Texture>(L"TopProp08Texture", L"top_prop08.png");
		Resources::Load<Texture>(L"HorizontalTexture", L"Rings\\horizontal.png");
		Resources::Load<Texture>(L"SlopedTexture", L"Rings\\sloped.png");
		Resources::Load<Texture>(L"VerticalTexture", L"Rings\\vertical.png");

		Resources::Load<Texture>(L"WallTexture", L"Wall.png");
		Resources::Load<Texture>(L"GrassTexture", L"Grass.png");
		Resources::Load<Texture>(L"CeilingTexture", L"ceiling.png");
#pragma endregion
#pragma region PLAYER TEXTURE
		Resources::Load<Texture>(L"StandTexture", L"sprOtusStand.png");
		Resources::Load<Texture>(L"GeddyTexture", L"Geddy\\sadIdle.png");
		Resources::Load<Texture>(L"GeddyArmTexture", L"Geddy\\arm_48x32.png");
		Resources::Load<Texture>(L"MechanicBulletTexture", L"Bullets\\sprMechanicBullet_38x31.png");
#pragma endregion
#pragma region MONSTER TEXTURE
		Resources::Load<Texture>(L"GawkTexture", L"Gawk\\sprGawkHurt_81x70.png");
#pragma endregion
#pragma region DYNAMIC TEXTURE
		std::shared_ptr<Texture> uavTexture = std::make_shared<Texture>();
		uavTexture->Create(1024, 1024, DXGI_FORMAT_R8G8B8A8_UNORM, D3D11_BIND_SHADER_RESOURCE
			| D3D11_BIND_UNORDERED_ACCESS);
		Resources::Insert<Texture>(L"PaintTexture", uavTexture);
#pragma endregion
#pragma region BACKROCK TEXTURE
		Resources::Load<Texture>(L"BackRockTexture", L"Vellie Cave\\backRock.png");
		Resources::Load<Texture>(L"BackRockShadowTexture", L"Vellie Cave\\backRockShadow.png");
		Resources::Load<Texture>(L"BackRock2Texture", L"Vellie Cave\\backRock2.png");
		Resources::Load<Texture>(L"BackRock2ShadowTexture", L"Vellie Cave\\backRock2Shadow.png");
		Resources::Load<Texture>(L"BackRock3Texture", L"Vellie Cave\\backRock3.png");
		Resources::Load<Texture>(L"BackRock3ShadowTexture", L"Vellie Cave\\backRock3Shadow.png");
#pragma endregion
#pragma region PLATFORM TEXTURE
		Resources::Load<Texture>(L"TotalCaveTexture", L"Test.png");
		Resources::Load<Texture>(L"TotalVillageTexture", L"TotalVillage.png");
		Resources::Load<Texture>(L"GrassFloorTexture", L"tileFloor.png");
		Resources::Load<Texture>(L"GrassSlopeTexture", L"Vellie-Tropos-Owl Temple assets\\grassSlope.png");
		Resources::Load<Texture>(L"Tile01Texture", L"Vellie-Tropos-Owl Temple assets\\tile01.png");
		Resources::Load<Texture>(L"Tile02Texture", L"Vellie-Tropos-Owl Temple assets\\tile02.png");
		Resources::Load<Texture>(L"Tile03Texture", L"Vellie-Tropos-Owl Temple assets\\tile03.png");
		Resources::Load<Texture>(L"Tile04Texture", L"Vellie-Tropos-Owl Temple assets\\tile04.png");

#pragma endregion
	}

	void LoadMaterial()
	{
#pragma region CAVESCENE MATERIAL
		std::shared_ptr <Texture> grasstexture = Resources::Find<Texture>(L"GrassTexture");
		std::shared_ptr<Shader> grassshader = Resources::Find<Shader>(L"SpriteShader");
		std::shared_ptr<Material> grassmaterial = std::make_shared<Material>();
		grassmaterial->SetRenderingMode(eRenderingMode::Transparent);
		grassmaterial->SetShader(grassshader);
		grassmaterial->SetTexture(eTextureSlot::T0, grasstexture);
		Resources::Insert<Material>(L"GrassMaterial", grassmaterial);

		std::shared_ptr <Texture> ceilingtexture = Resources::Find<Texture>(L"CeilingTexture");
		std::shared_ptr<Shader> ceilingshader = Resources::Find<Shader>(L"SpriteShader");
		std::shared_ptr<Material> ceilingmaterial = std::make_shared<Material>();
		ceilingmaterial->SetRenderingMode(eRenderingMode::Transparent);
		ceilingmaterial->SetShader(ceilingshader);
		ceilingmaterial->SetTexture(eTextureSlot::T0, ceilingtexture);
		Resources::Insert<Material>(L"CeilingMaterial", ceilingmaterial);

		std::shared_ptr <Texture> walltexture = Resources::Find<Texture>(L"WallTexture");
		std::shared_ptr<Shader> wallshader = Resources::Find<Shader>(L"SpriteShader");
		std::shared_ptr<Material> wallmaterial = std::make_shared<Material>();
		wallmaterial->SetRenderingMode(eRenderingMode::Transparent);
		wallmaterial->SetShader(wallshader);
		wallmaterial->SetTexture(eTextureSlot::T0, walltexture);
		Resources::Insert<Material>(L"WallMaterial", wallmaterial);
#pragma endregion
#pragma region PLATFORM MATERIAL
		std::shared_ptr <Texture> totalcavetexture = Resources::Find<Texture>(L"TotalCaveTexture");
		std::shared_ptr<Shader> totalcaveshader = Resources::Find<Shader>(L"SpriteShader");
		std::shared_ptr<Material> totalcavematerial = std::make_shared<Material>();
		totalcavematerial->SetRenderingMode(eRenderingMode::Transparent);
		totalcavematerial->SetShader(totalcaveshader);
		totalcavematerial->SetTexture(eTextureSlot::T0, totalcavetexture);
		Resources::Insert<Material>(L"TotalCaveMaterial", totalcavematerial);

		std::shared_ptr <Texture> totalvillagetexture = Resources::Find<Texture>(L"TotalVillageTexture");
		std::shared_ptr<Shader> totalvillageshader = Resources::Find<Shader>(L"SpriteShader");
		std::shared_ptr<Material> totalvillagematerial = std::make_shared<Material>();
		totalvillagematerial->SetRenderingMode(eRenderingMode::Transparent);
		totalvillagematerial->SetShader(totalvillageshader);
		totalvillagematerial->SetTexture(eTextureSlot::T0, totalvillagetexture);
		Resources::Insert<Material>(L"TotalVillageMaterial", totalvillagematerial);

		std::shared_ptr <Texture> grassfloortexture = Resources::Find<Texture>(L"GrassFloorTexture");
		std::shared_ptr<Shader> grassfloorshader = Resources::Find<Shader>(L"SpriteShader");
		std::shared_ptr<Material> grassfloormaterial = std::make_shared<Material>();
		grassfloormaterial->SetRenderingMode(eRenderingMode::Transparent);
		grassfloormaterial->SetShader(grassfloorshader);
		grassfloormaterial->SetTexture(eTextureSlot::T0, grassfloortexture);
		Resources::Insert<Material>(L"GrassFloorMaterial", grassfloormaterial);

		std::shared_ptr <Texture> grassslopetexture = Resources::Find<Texture>(L"GrassSlopeTexture");
		std::shared_ptr<Shader> grassslopeshader = Resources::Find<Shader>(L"SpriteShader");
		std::shared_ptr<Material> grassslopematerial = std::make_shared<Material>();
		grassslopematerial->SetRenderingMode(eRenderingMode::Transparent);
		grassslopematerial->SetShader(grassslopeshader);
		grassslopematerial->SetTexture(eTextureSlot::T0, grassslopetexture);
		Resources::Insert<Material>(L"GrassSlopeMaterial", grassslopematerial);

		std::shared_ptr <Texture> tile01texture = Resources::Find<Texture>(L"Tile01Texture");
		std::shared_ptr<Shader> tile01shader = Resources::Find<Shader>(L"SpriteShader");
		std::shared_ptr<Material> tile01material = std::make_shared<Material>();
		tile01material->SetRenderingMode(eRenderingMode::Transparent);
		tile01material->SetShader(tile01shader);
		tile01material->SetTexture(eTextureSlot::T0, tile01texture);
		Resources::Insert<Material>(L"Tile01Material", tile01material);

		std::shared_ptr <Texture> tile02texture = Resources::Find<Texture>(L"Tile02Texture");
		std::shared_ptr<Shader> tile02shader = Resources::Find<Shader>(L"SpriteShader");
		std::shared_ptr<Material> tile02material = std::make_shared<Material>();
		tile02material->SetRenderingMode(eRenderingMode::Transparent);
		tile02material->SetShader(tile02shader);
		tile02material->SetTexture(eTextureSlot::T0, tile02texture);
		Resources::Insert<Material>(L"Tile02Material", tile02material);

		std::shared_ptr <Texture> tile03texture = Resources::Find<Texture>(L"Tile03Texture");
		std::shared_ptr<Shader> tile03shader = Resources::Find<Shader>(L"SpriteShader");
		std::shared_ptr<Material> tile03material = std::make_shared<Material>();
		tile03material->SetRenderingMode(eRenderingMode::Transparent);
		tile03material->SetShader(tile03shader);
		tile03material->SetTexture(eTextureSlot::T0, tile03texture);
		Resources::Insert<Material>(L"Tile03Material", tile03material);

		std::shared_ptr <Texture> tile04texture = Resources::Find<Texture>(L"Tile04Texture");
		std::shared_ptr<Shader> tile04shader = Resources::Find<Shader>(L"SpriteShader");
		std::shared_ptr<Material> tile04material = std::make_shared<Material>();
		tile04material->SetRenderingMode(eRenderingMode::Transparent);
		tile04material->SetShader(tile04shader);
		tile04material->SetTexture(eTextureSlot::T0, tile04texture);
		Resources::Insert<Material>(L"Tile04Material", tile04material);

#pragma endregion
#pragma region BACKROCK MATERIAL
		std::shared_ptr <Texture> backrockTexture = Resources::Find<Texture>(L"BackRockTexture");
		std::shared_ptr<Shader> backrockshader = Resources::Find<Shader>(L"SpriteShader");
		std::shared_ptr<Material> backrockmaterial = std::make_shared<Material>();
		backrockmaterial->SetRenderingMode(eRenderingMode::Transparent);
		backrockmaterial->SetShader(backrockshader);
		backrockmaterial->SetTexture(eTextureSlot::T0, backrockTexture);
		Resources::Insert<Material>(L"BackRockMaterial", backrockmaterial);

		std::shared_ptr <Texture> backrockshadowTexture = Resources::Find<Texture>(L"BackRockShadowTexture");
		std::shared_ptr<Shader> backrockshadowshader = Resources::Find<Shader>(L"SpriteShader");
		std::shared_ptr<Material> backrockshadowmaterial = std::make_shared<Material>();
		backrockshadowmaterial->SetRenderingMode(eRenderingMode::Transparent);
		backrockshadowmaterial->SetShader(backrockshadowshader);
		backrockshadowmaterial->SetTexture(eTextureSlot::T0, backrockshadowTexture);
		Resources::Insert<Material>(L"BackRockShadowMaterial", backrockshadowmaterial);

		std::shared_ptr <Texture> backrock2Texture = Resources::Find<Texture>(L"BackRock2Texture");
		std::shared_ptr<Shader> backrock2shader = Resources::Find<Shader>(L"SpriteShader");
		std::shared_ptr<Material> backrock2material = std::make_shared<Material>();
		backrock2material->SetRenderingMode(eRenderingMode::Transparent);
		backrock2material->SetShader(backrock2shader);
		backrock2material->SetTexture(eTextureSlot::T0, backrock2Texture);
		Resources::Insert<Material>(L"BackRock2Material", backrock2material);

		std::shared_ptr <Texture> backrock2shadowTexture = Resources::Find<Texture>(L"BackRock2ShadowTexture");
		std::shared_ptr<Shader> backrock2shadowshader = Resources::Find<Shader>(L"SpriteShader");
		std::shared_ptr<Material> backrock2shadowmaterial = std::make_shared<Material>();
		backrock2shadowmaterial->SetRenderingMode(eRenderingMode::Transparent);
		backrock2shadowmaterial->SetShader(backrock2shadowshader);
		backrock2shadowmaterial->SetTexture(eTextureSlot::T0, backrock2shadowTexture);
		Resources::Insert<Material>(L"BackRock2ShadowMaterial", backrock2shadowmaterial);

		std::shared_ptr <Texture> backrock3Texture = Resources::Find<Texture>(L"BackRock3Texture");
		std::shared_ptr<Shader> backrock3shader = Resources::Find<Shader>(L"SpriteShader");
		std::shared_ptr<Material> backrock3material = std::make_shared<Material>();
		backrock3material->SetRenderingMode(eRenderingMode::Transparent);
		backrock3material->SetShader(backrock3shader);
		backrock3material->SetTexture(eTextureSlot::T0, backrock3Texture);
		Resources::Insert<Material>(L"BackRock3Material", backrock3material);

		std::shared_ptr <Texture> backrock3shadowTexture = Resources::Find<Texture>(L"BackRock3ShadowTexture");
		std::shared_ptr<Shader> backrock3shadowshader = Resources::Find<Shader>(L"SpriteShader");
		std::shared_ptr<Material> backrock3shadowmaterial = std::make_shared<Material>();
		backrock3shadowmaterial->SetRenderingMode(eRenderingMode::Transparent);
		backrock3shadowmaterial->SetShader(backrock3shadowshader);
		backrock3shadowmaterial->SetTexture(eTextureSlot::T0, backrock3shadowTexture);
		Resources::Insert<Material>(L"BackRock3ShadowMaterial", backrock3shadowmaterial);
#pragma endregion
#pragma region TITLESCENE MATERIAL

		std::shared_ptr <Texture> grasshillTexture = Resources::Find<Texture>(L"LeftOtusTexture");
		std::shared_ptr<Shader> grasshillsshader = Resources::Find<Shader>(L"SpriteShader");
		std::shared_ptr<Material> grasshillmaterial = std::make_shared<Material>();
		grasshillmaterial->SetRenderingMode(eRenderingMode::Transparent);
		grasshillmaterial->SetShader(grasshillsshader);
		grasshillmaterial->SetTexture(eTextureSlot::T0, grasshillTexture);
		Resources::Insert<Material>(L"GrassHillmaterial", grasshillmaterial);

		std::shared_ptr <Texture> grasspathwayTexture = Resources::Find<Texture>(L"LeftOtusTexture");
		std::shared_ptr<Shader> grasspathwayshader = Resources::Find<Shader>(L"SpriteShader");
		std::shared_ptr<Material> grasspathwaymaterial = std::make_shared<Material>();
		grasspathwaymaterial->SetRenderingMode(eRenderingMode::Transparent);
		grasspathwaymaterial->SetShader(grasspathwayshader);
		grasspathwaymaterial->SetTexture(eTextureSlot::T0, grasspathwayTexture);
		Resources::Insert<Material>(L"GrassPathwaymaterial", grasspathwaymaterial);

		std::shared_ptr <Texture> leftotusTexture = Resources::Find<Texture>(L"LeftOtusTexture");
		std::shared_ptr<Shader> leftotusshader = Resources::Find<Shader>(L"SpriteShader");
		std::shared_ptr<Material> leftotusmaterial = std::make_shared<Material>();
		leftotusmaterial->SetRenderingMode(eRenderingMode::Transparent);
		leftotusmaterial->SetShader(leftotusshader);
		leftotusmaterial->SetTexture(eTextureSlot::T0, leftotusTexture);
		Resources::Insert<Material>(L"LeftOtusmaterial", leftotusmaterial);


		std::shared_ptr <Texture> titleskytexture = Resources::Find<Texture>(L"TitleSkyTexture");
		std::shared_ptr<Shader> titleskyshader = Resources::Find<Shader>(L"SpriteShader");
		std::shared_ptr<Material> titleskymaterial = std::make_shared<Material>();
		titleskymaterial->SetRenderingMode(eRenderingMode::Transparent);
		titleskymaterial->SetShader(titleskyshader);
		titleskymaterial->SetTexture(eTextureSlot::T0,titleskytexture);
		Resources::Insert<Material>(L"Titleskymaterial", titleskymaterial);

		std::shared_ptr <Texture> owlboylogotexture = Resources::Find<Texture>(L"OwlboyLogoTexture");
		std::shared_ptr<Shader> owlboylogoshader = Resources::Find<Shader>(L"SpriteShader");
		std::shared_ptr<Material> owlboylogomaterial = std::make_shared<Material>();
		owlboylogomaterial->SetRenderingMode(eRenderingMode::Transparent);
		owlboylogomaterial->SetShader(owlboylogoshader);
		owlboylogomaterial->SetTexture(eTextureSlot::T0, owlboylogotexture);
		Resources::Insert<Material>(L"OwlboyLogomaterial", owlboylogomaterial);

		std::shared_ptr <Texture> titlerighttexture = Resources::Find<Texture>(L"TitleRightTexture");
		std::shared_ptr<Shader> titlerightshader = Resources::Find<Shader>(L"SpriteShader");
		std::shared_ptr<Material> titlerightmaterial = std::make_shared<Material>();
		titlerightmaterial->SetRenderingMode(eRenderingMode::Transparent);
		titlerightmaterial->SetShader(titlerightshader);
		titlerightmaterial->SetTexture(eTextureSlot::T0, titlerighttexture);
		Resources::Insert<Material>(L"TitleRightmaterial", titlerightmaterial);

		std::shared_ptr <Texture> titlelefttexture = Resources::Find<Texture>(L"TitleLeftTexture");
		std::shared_ptr<Shader> titleleftshader = Resources::Find<Shader>(L"SpriteShader");
		std::shared_ptr<Material> titleleftmaterial = std::make_shared<Material>();
		titleleftmaterial->SetRenderingMode(eRenderingMode::Transparent);
		titleleftmaterial->SetShader(titleleftshader);
		titleleftmaterial->SetTexture(eTextureSlot::T0, titlelefttexture);
		Resources::Insert<Material>(L"TitleLeftmaterial", titleleftmaterial);

	
#pragma endregion
#pragma region BACKGROUND MATERIAL
		std::shared_ptr <Texture> verticaltexture = Resources::Find<Texture>(L"VerticalTexture");
		std::shared_ptr<Shader> verticalshader = Resources::Find<Shader>(L"SpriteShader");
		std::shared_ptr<Material> verticalmaterial = std::make_shared<Material>();
		verticalmaterial->SetRenderingMode(eRenderingMode::Transparent);
		verticalmaterial->SetShader(verticalshader);
		verticalmaterial->SetTexture(eTextureSlot::T0, verticaltexture);
		Resources::Insert<Material>(L"Verticalmaterial", verticalmaterial);

		std::shared_ptr <Texture> Slopedtexture = Resources::Find<Texture>(L"SlopedTexture");
		std::shared_ptr<Shader> Slopedshader = Resources::Find<Shader>(L"SpriteShader");
		std::shared_ptr<Material> Slopedmaterial = std::make_shared<Material>();
		Slopedmaterial->SetRenderingMode(eRenderingMode::Transparent);
		Slopedmaterial->SetShader(Slopedshader);
		Slopedmaterial->SetTexture(eTextureSlot::T0, Slopedtexture);
		Resources::Insert<Material>(L"Slopedmaterial", Slopedmaterial);

		std::shared_ptr <Texture> horizontaltexture = Resources::Find<Texture>(L"HorizontalTexture");
		std::shared_ptr<Shader> horizontalshader = Resources::Find<Shader>(L"SpriteShader");
		std::shared_ptr<Material> horizontalmaterial = std::make_shared<Material>();
		horizontalmaterial->SetRenderingMode(eRenderingMode::Transparent);
		horizontalmaterial->SetShader(horizontalshader);
		horizontalmaterial->SetTexture(eTextureSlot::T0, horizontaltexture);
		Resources::Insert<Material>(L"Horizontalmaterial", horizontalmaterial);

		std::shared_ptr <Texture> backskytexture = Resources::Find<Texture>(L"BackSkyTexture");
		std::shared_ptr<Shader> backskyshader = Resources::Find<Shader>(L"SpriteShader");
		std::shared_ptr<Material> backskymaterial = std::make_shared<Material>();
		backskymaterial->SetRenderingMode(eRenderingMode::Transparent);
		backskymaterial->SetShader(backskyshader);
		backskymaterial->SetTexture(eTextureSlot::T0, backskytexture);
		Resources::Insert<Material>(L"Backskymaterial", backskymaterial);

		std::shared_ptr <Texture> hpbartexture = Resources::Find<Texture>(L"HpBarTexture");
		std::shared_ptr<Shader> hpbarshader = Resources::Find<Shader>(L"UIShader");
		std::shared_ptr<Material> hpbarmaterial = std::make_shared<Material>();
		hpbarmaterial->SetRenderingMode(eRenderingMode::Transparent);
		hpbarmaterial->SetShader(hpbarshader);
		hpbarmaterial->SetTexture(eTextureSlot::T0, hpbartexture);
		Resources::Insert<Material>(L"Hpbarmaterial", hpbarmaterial);

		std::shared_ptr <Texture> tilefloortexture = Resources::Find<Texture>(L"TileFloorTexture");
		std::shared_ptr<Shader> tilefloorshader = Resources::Find<Shader>(L"SpriteShader");
		std::shared_ptr<Material> tilefloormaterial = std::make_shared<Material>();
		tilefloormaterial->SetRenderingMode(eRenderingMode::Transparent);
		tilefloormaterial->SetShader(tilefloorshader);
		tilefloormaterial->SetTexture(eTextureSlot::T0, tilefloortexture);
		Resources::Insert<Material>(L"Tilefloormaterial", tilefloormaterial);

		std::shared_ptr <Texture> topprop08texture = Resources::Find<Texture>(L"TopProp08Texture");
		std::shared_ptr<Shader> topprop08shader = Resources::Find<Shader>(L"SpriteShader");
		std::shared_ptr<Material> topprop08material = std::make_shared<Material>();
		topprop08material->SetRenderingMode(eRenderingMode::Transparent);
		topprop08material->SetShader(topprop08shader);
		topprop08material->SetTexture(eTextureSlot::T0, topprop08texture);
		Resources::Insert<Material>(L"TopProp08material", topprop08material);
#pragma endregion
#pragma region PLAYER MATERIAL
		std::shared_ptr <Texture> mechanicbullettexture = Resources::Find<Texture>(L"MechanicBulletTexture");
		std::shared_ptr<Shader> mechanicbulletshader = Resources::Find<Shader>(L"SpriteShader");
		std::shared_ptr<Material> mechanicbulletmaterial = std::make_shared<Material>();
		mechanicbulletmaterial->SetRenderingMode(eRenderingMode::Transparent);
		mechanicbulletmaterial->SetShader(mechanicbulletshader);
		mechanicbulletmaterial->SetTexture(eTextureSlot::T0, mechanicbullettexture);
		Resources::Insert<Material>(L"Mechanicbulletmaterial", mechanicbulletmaterial);

		std::shared_ptr <Texture> geddyarmtexture = Resources::Find<Texture>(L"GeddyArmTexture");
		std::shared_ptr<Shader> geddarmshader = Resources::Find<Shader>(L"SpriteShader");
		std::shared_ptr<Material> geddyarmmaterial = std::make_shared<Material>();
		geddyarmmaterial->SetRenderingMode(eRenderingMode::Transparent);
		geddyarmmaterial->SetShader(geddarmshader);
		geddyarmmaterial->SetTexture(eTextureSlot::T0, geddyarmtexture);
		Resources::Insert<Material>(L"GeddyArmmaterial", geddyarmmaterial);

		std::shared_ptr <Texture> geddytexture = Resources::Find<Texture>(L"GeddyTexture");
		std::shared_ptr<Shader> geddyshader = Resources::Find<Shader>(L"SpriteShader");
		std::shared_ptr<Material> geddymaterial = std::make_shared<Material>();
		geddymaterial->SetRenderingMode(eRenderingMode::Transparent);
		geddymaterial->SetShader(geddyshader);
		geddymaterial->SetTexture(eTextureSlot::T0, geddytexture);
		Resources::Insert<Material>(L"Geddymaterial", geddymaterial);

		std::shared_ptr <Texture> standtexture = Resources::Find<Texture>(L"StandTexture");
		std::shared_ptr<Shader> standshader = Resources::Find<Shader>(L"SpriteShader");
		std::shared_ptr<Material> standmaterial = std::make_shared<Material>();
		standmaterial->SetRenderingMode(eRenderingMode::Transparent);
		standmaterial->SetShader(standshader);
		standmaterial->SetTexture(eTextureSlot::T0, standtexture);
		Resources::Insert<Material>(L"Standmaterial", standmaterial);
#pragma endregion
#pragma region MONSTER MATERIAL
		std::shared_ptr <Texture> gawktexture = Resources::Find<Texture>(L"GawkTexture");
		std::shared_ptr<Shader> gawkshader = Resources::Find<Shader>(L"SpriteShader");
		std::shared_ptr<Material> gawkmaterial = std::make_shared<Material>();
		gawkmaterial->SetRenderingMode(eRenderingMode::Transparent);
		gawkmaterial->SetShader(gawkshader);
		gawkmaterial->SetTexture(eTextureSlot::T0, gawktexture);
		Resources::Insert<Material>(L"GawkMaterial", gawkmaterial);
#pragma endregion
#pragma region DEFAULT
		std::shared_ptr <Texture> texture = Resources::Find<Texture>(L"PaintTexture");
		std::shared_ptr<Shader> shader = Resources::Find<Shader>(L"RectShader");
		std::shared_ptr<Material> material = std::make_shared<Material>();
		material->SetShader(shader);
		material->SetTexture(eTextureSlot::T0, texture);
		Resources::Insert<Material>(L"RectMaterial", material);
#pragma endregion
#pragma region SPRITE
		std::shared_ptr <Texture> spriteTexture = Resources::Find<Texture>(L"DefaultSprite");
		std::shared_ptr<Shader> spriteShader = Resources::Find<Shader>(L"SpriteShader");
		std::shared_ptr<Material> spriteMaterial = std::make_shared<Material>();
		spriteMaterial->SetRenderingMode(eRenderingMode::Transparent);
		spriteMaterial->SetShader(spriteShader);
		spriteMaterial->SetTexture(eTextureSlot::T0, spriteTexture);
		Resources::Insert<Material>(L"SpriteMaterial", spriteMaterial);
#pragma endregion
#pragma region UI
		std::shared_ptr <Texture> uiTexture = Resources::Find<Texture>(L"HPBarTexture");
		std::shared_ptr<Shader> uiShader = Resources::Find<Shader>(L"UIShader");
		std::shared_ptr<Material> uiMaterial = std::make_shared<Material>();
		uiMaterial->SetRenderingMode(eRenderingMode::Transparent);
		uiMaterial->SetShader(uiShader);
		uiMaterial->SetTexture(eTextureSlot::T0, uiTexture);
		Resources::Insert<Material>(L"UIMaterial", uiMaterial);
#pragma endregion
#pragma region GRID
		std::shared_ptr<Shader> gridShader = Resources::Find<Shader>(L"GridShader");
		std::shared_ptr<Material> gridMaterial = std::make_shared<Material>();
		gridMaterial->SetShader(gridShader);
		Resources::Insert<Material>(L"GridMaterial", gridMaterial);
#pragma endregion
#pragma region FADE
		std::shared_ptr<Shader> fadeInShader = Resources::Find<Shader>(L"FadeInShader");
		std::shared_ptr<Material> fadeInMaterial = std::make_shared<Material>();
		fadeInMaterial->SetShader(fadeInShader);
		Resources::Insert<Material>(L"FadeInMaterial", fadeInMaterial);
#pragma endregion
#pragma region DEBUG
		std::shared_ptr<Shader> debugShader = Resources::Find<Shader>(L"DebugShader");
		std::shared_ptr<Material> debugMaterial = std::make_shared<Material>();
		debugMaterial->SetRenderingMode(eRenderingMode::Transparent);
		debugMaterial->SetShader(debugShader);
		Resources::Insert<Material>(L"DebugMaterial", debugMaterial);
#pragma endregion
#pragma region PARTICLE
		std::shared_ptr<Shader> particleShader = Resources::Find<Shader>(L"ParticleShader");
		std::shared_ptr<Material> particleMaterial = std::make_shared<Material>();
		particleMaterial->SetRenderingMode(eRenderingMode::Transparent);
		particleMaterial->SetShader(particleShader);
		Resources::Insert<Material>(L"ParticleMaterial", particleMaterial);
#pragma endregion
#pragma region POSTPROCESS
		std::shared_ptr<Shader> postProcessShader = Resources::Find<Shader>(L"PostProcessShader");
		std::shared_ptr<Material> postProcessMaterial = std::make_shared<Material>();
		postProcessMaterial->SetRenderingMode(eRenderingMode::PostProcess);
		postProcessMaterial->SetShader(postProcessShader);
		Resources::Insert<Material>(L"PostProcessMaterial", postProcessMaterial);
#pragma endregion
	}


	void Initialize()
	{
		LoadMesh();
		LoadShader();
		SetUpState();
		LoadBuffer();
		LoadTexture();
		LoadMaterial();
	}

	void Release()
	{
		for (size_t i = 0; i < (UINT)eCBType::End; i++)
		{
			delete constantBuffers[i];
			constantBuffers[i] = nullptr;
		}
		delete lightsBuffer;
		lightsBuffer = nullptr;
	}

	void Render()
	{
		BindNoiseTexture();
		BindLights();

		eSceneType type = SceneManager::GetActiveScene()->GetSceneType();
		for (Camera* cam : cameras[(UINT)type])
		{
			if (cam == nullptr)
				continue;

			cam->Render();
		}

		cameras[(UINT)type].clear();
		renderer::lights.clear();
	}

	void PushLightAttribute(LightAttribute lightAttribute)
	{
		lights.push_back(lightAttribute);
	}

	void BindLights()
	{
		lightsBuffer->SetData(lights.data(), lights.size());
		lightsBuffer->BindSRV(eShaderStage::VS, 13);
		lightsBuffer->BindSRV(eShaderStage::PS, 13);

		renderer::LightCB trCb = {};
		trCb.numberOfLight = lights.size();

		ConstantBuffer* cb = renderer::constantBuffers[(UINT)eCBType::Light];
		cb->SetData(&trCb);
		cb->Bind(eShaderStage::VS);
		cb->Bind(eShaderStage::PS);
	}

	float noiseTime = 10.0f;
	void BindNoiseTexture()
	{
		std::shared_ptr<Texture> noise = Resources::Find<Texture>(L"noise_01");
		noise->BindShaderResource(eShaderStage::VS, 16);
		noise->BindShaderResource(eShaderStage::HS, 16);
		noise->BindShaderResource(eShaderStage::DS, 16);
		noise->BindShaderResource(eShaderStage::GS, 16);
		noise->BindShaderResource(eShaderStage::PS, 16);
		noise->BindShaderResource(eShaderStage::CS, 16);

		NoiseCB info = {};
		info.noiseSize.x = noise->GetWidth();
		info.noiseSize.y = noise->GetHeight();
		noiseTime -= Time::DeltaTime();
		info.noiseTime = noiseTime;

		ConstantBuffer* cb = renderer::constantBuffers[(UINT)eCBType::Noise];
		cb->SetData(&info);
		cb->Bind(eShaderStage::VS);
		cb->Bind(eShaderStage::HS);
		cb->Bind(eShaderStage::DS);
		cb->Bind(eShaderStage::GS);
		cb->Bind(eShaderStage::PS);
		cb->Bind(eShaderStage::CS);
	}

	void CopyRenderTarget()
	{
		std::shared_ptr<Texture> renderTarget = Resources::Find<Texture>(L"RenderTargetTexture");

		ID3D11ShaderResourceView* srv = nullptr;
		GetDevice()->BindShaderResource(eShaderStage::PS, 60, &srv);

		ID3D11Texture2D* dest = postProcessTexture->GetTexture().Get();
		ID3D11Texture2D* source = renderTarget->GetTexture().Get();

		GetDevice()->CopyResource(dest, source);

		postProcessTexture->BindShaderResource(eShaderStage::PS, 60);
	}



}