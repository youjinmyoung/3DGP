//-----------------------------------------------------------------------------
// File: Shader.cpp
//-----------------------------------------------------------------------------

#include "stdafx.h"
#include "Shader.h"
#include "DDSTextureLoader12.h"

CShader::CShader()
{
	m_d3dSrvCPUDescriptorStartHandle.ptr = m_d3dCbvCPUDescriptorStartHandle.ptr = NULL;
	m_d3dSrvGPUDescriptorStartHandle.ptr = m_d3dCbvGPUDescriptorStartHandle.ptr = NULL;
}

CShader::~CShader()
{
	if (m_ppd3dPipelineStates) m_ppd3dPipelineStates[0]->Release();
}

D3D12_SHADER_BYTECODE CShader::CreateVertexShader(ID3DBlob **ppd3dShaderBlob)
{
	D3D12_SHADER_BYTECODE d3dShaderByteCode;
	d3dShaderByteCode.BytecodeLength = 0;
	d3dShaderByteCode.pShaderBytecode = NULL;

	return(d3dShaderByteCode);
}

D3D12_SHADER_BYTECODE CShader::CreatePixelShader(ID3DBlob **ppd3dShaderBlob)
{
	D3D12_SHADER_BYTECODE d3dShaderByteCode;
	d3dShaderByteCode.BytecodeLength = 0;
	d3dShaderByteCode.pShaderBytecode = NULL;

	return(d3dShaderByteCode);
}

D3D12_SHADER_BYTECODE CShader::CreateGeometryShader(ID3DBlob **ppd3dShaderBlob)
{
	D3D12_SHADER_BYTECODE d3dShaderByteCode;
	d3dShaderByteCode.BytecodeLength = 0;
	d3dShaderByteCode.pShaderBytecode = NULL;

	return(d3dShaderByteCode);
}

D3D12_SHADER_BYTECODE CShader::CompileShaderFromFile(WCHAR *pszFileName, LPCSTR pszShaderName, LPCSTR pszShaderProfile, ID3DBlob **ppd3dShaderBlob)
{
	UINT nCompileFlags = 0;
#if defined(_DEBUG)
	nCompileFlags = D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION;
#endif

	ID3DBlob *pd3dErrorBlob = NULL;
	::D3DCompileFromFile(pszFileName, NULL, D3D_COMPILE_STANDARD_FILE_INCLUDE, pszShaderName, pszShaderProfile, nCompileFlags, 0, ppd3dShaderBlob, NULL);
	//	char *pErrorString = (char *)pd3dErrorBlob->GetBufferPointer();

	D3D12_SHADER_BYTECODE d3dShaderByteCode;
	d3dShaderByteCode.BytecodeLength = (*ppd3dShaderBlob)->GetBufferSize();
	d3dShaderByteCode.pShaderBytecode = (*ppd3dShaderBlob)->GetBufferPointer();

	return(d3dShaderByteCode);
}

D3D12_INPUT_LAYOUT_DESC CShader::CreateInputLayout()
{
	D3D12_INPUT_LAYOUT_DESC d3dInputLayoutDesc;
	d3dInputLayoutDesc.pInputElementDescs = NULL;
	d3dInputLayoutDesc.NumElements = 0;

	return(d3dInputLayoutDesc);
}

D3D12_RASTERIZER_DESC CShader::CreateRasterizerState()
{
	D3D12_RASTERIZER_DESC d3dRasterizerDesc;
	::ZeroMemory(&d3dRasterizerDesc, sizeof(D3D12_RASTERIZER_DESC));
	d3dRasterizerDesc.FillMode = D3D12_FILL_MODE_SOLID;
	d3dRasterizerDesc.CullMode = D3D12_CULL_MODE_BACK;
	d3dRasterizerDesc.FrontCounterClockwise = FALSE;
	d3dRasterizerDesc.DepthBias = 0;
	d3dRasterizerDesc.DepthBiasClamp = 0.0f;
	d3dRasterizerDesc.SlopeScaledDepthBias = 0.0f;
	d3dRasterizerDesc.DepthClipEnable = TRUE;
	d3dRasterizerDesc.MultisampleEnable = FALSE;
	d3dRasterizerDesc.AntialiasedLineEnable = FALSE;
	d3dRasterizerDesc.ForcedSampleCount = 0;
	d3dRasterizerDesc.ConservativeRaster = D3D12_CONSERVATIVE_RASTERIZATION_MODE_OFF;

	return(d3dRasterizerDesc);
}

D3D12_DEPTH_STENCIL_DESC CShader::CreateDepthStencilState()
{
	D3D12_DEPTH_STENCIL_DESC d3dDepthStencilDesc;
	::ZeroMemory(&d3dDepthStencilDesc, sizeof(D3D12_DEPTH_STENCIL_DESC));
	d3dDepthStencilDesc.DepthEnable = TRUE;
	d3dDepthStencilDesc.DepthWriteMask = D3D12_DEPTH_WRITE_MASK_ALL;
	d3dDepthStencilDesc.DepthFunc = D3D12_COMPARISON_FUNC_LESS;
	d3dDepthStencilDesc.StencilEnable = FALSE;
	d3dDepthStencilDesc.StencilReadMask = 0x00;
	d3dDepthStencilDesc.StencilWriteMask = 0x00;
	d3dDepthStencilDesc.FrontFace.StencilFailOp = D3D12_STENCIL_OP_KEEP;
	d3dDepthStencilDesc.FrontFace.StencilDepthFailOp = D3D12_STENCIL_OP_KEEP;
	d3dDepthStencilDesc.FrontFace.StencilPassOp = D3D12_STENCIL_OP_KEEP;
	d3dDepthStencilDesc.FrontFace.StencilFunc = D3D12_COMPARISON_FUNC_NEVER;
	d3dDepthStencilDesc.BackFace.StencilFailOp = D3D12_STENCIL_OP_KEEP;
	d3dDepthStencilDesc.BackFace.StencilDepthFailOp = D3D12_STENCIL_OP_KEEP;
	d3dDepthStencilDesc.BackFace.StencilPassOp = D3D12_STENCIL_OP_KEEP;
	d3dDepthStencilDesc.BackFace.StencilFunc = D3D12_COMPARISON_FUNC_NEVER;

	return(d3dDepthStencilDesc);
}

D3D12_BLEND_DESC CShader::CreateBlendState()
{
	D3D12_BLEND_DESC d3dBlendDesc;
	::ZeroMemory(&d3dBlendDesc, sizeof(D3D12_BLEND_DESC));
	d3dBlendDesc.AlphaToCoverageEnable = FALSE;
	d3dBlendDesc.IndependentBlendEnable = FALSE;
	d3dBlendDesc.RenderTarget[0].BlendEnable = FALSE;
	d3dBlendDesc.RenderTarget[0].LogicOpEnable = FALSE;
	d3dBlendDesc.RenderTarget[0].SrcBlend = D3D12_BLEND_ONE;
	d3dBlendDesc.RenderTarget[0].DestBlend = D3D12_BLEND_ZERO;
	d3dBlendDesc.RenderTarget[0].BlendOp = D3D12_BLEND_OP_ADD;
	d3dBlendDesc.RenderTarget[0].SrcBlendAlpha = D3D12_BLEND_ONE;
	d3dBlendDesc.RenderTarget[0].DestBlendAlpha = D3D12_BLEND_ZERO;
	d3dBlendDesc.RenderTarget[0].BlendOpAlpha = D3D12_BLEND_OP_ADD;
	d3dBlendDesc.RenderTarget[0].LogicOp = D3D12_LOGIC_OP_NOOP;
	d3dBlendDesc.RenderTarget[0].RenderTargetWriteMask = D3D12_COLOR_WRITE_ENABLE_ALL;

	return(d3dBlendDesc);
}

void CShader::CreateShader(ID3D12Device *pd3dDevice, ID3D12RootSignature *pd3dGraphicsRootSignature, UINT nRenderTargets)
{
	ID3DBlob *pd3dVertexShaderBlob = NULL, *pd3dPixelShaderBlob = NULL, *pd3dGeometryShaderBlob = NULL;

	D3D12_GRAPHICS_PIPELINE_STATE_DESC d3dPipelineStateDesc;
	::ZeroMemory(&d3dPipelineStateDesc, sizeof(D3D12_GRAPHICS_PIPELINE_STATE_DESC));
	d3dPipelineStateDesc.pRootSignature = pd3dGraphicsRootSignature;
	d3dPipelineStateDesc.VS = CreateVertexShader(&pd3dVertexShaderBlob);
	d3dPipelineStateDesc.GS = CreateGeometryShader(&pd3dGeometryShaderBlob);
	d3dPipelineStateDesc.PS = CreatePixelShader(&pd3dPixelShaderBlob);
	d3dPipelineStateDesc.RasterizerState = CreateRasterizerState();
	d3dPipelineStateDesc.BlendState = CreateBlendState();
	d3dPipelineStateDesc.DepthStencilState = CreateDepthStencilState();
	
	d3dPipelineStateDesc.InputLayout = CreateInputLayout();
	d3dPipelineStateDesc.SampleMask = UINT_MAX;
	d3dPipelineStateDesc.PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;
	d3dPipelineStateDesc.NumRenderTargets = 1;
	d3dPipelineStateDesc.RTVFormats[0] = DXGI_FORMAT_R8G8B8A8_UNORM;
	d3dPipelineStateDesc.DSVFormat = DXGI_FORMAT_D24_UNORM_S8_UINT;
	d3dPipelineStateDesc.SampleDesc.Count = 1;
	d3dPipelineStateDesc.Flags = D3D12_PIPELINE_STATE_FLAG_NONE;
	HRESULT hResult = pd3dDevice->CreateGraphicsPipelineState(&d3dPipelineStateDesc, __uuidof(ID3D12PipelineState), (void **)&m_ppd3dPipelineStates[0]);

	if (pd3dVertexShaderBlob) pd3dVertexShaderBlob->Release();
	if (pd3dPixelShaderBlob) pd3dPixelShaderBlob->Release();
	if (pd3dGeometryShaderBlob) pd3dGeometryShaderBlob->Release();
	if (d3dPipelineStateDesc.InputLayout.pInputElementDescs) delete[] d3dPipelineStateDesc.InputLayout.pInputElementDescs;
}

void CShader::CreateCbvAndSrvDescriptorHeaps(ID3D12Device *pd3dDevice, ID3D12GraphicsCommandList *pd3dCommandList, int nConstantBufferViews, int nShaderResourceViews)
{
	D3D12_DESCRIPTOR_HEAP_DESC d3dDescriptorHeapDesc;
	d3dDescriptorHeapDesc.NumDescriptors = nConstantBufferViews + nShaderResourceViews; //CBVs + SRVs 
	d3dDescriptorHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;
	d3dDescriptorHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;
	d3dDescriptorHeapDesc.NodeMask = 0;
	pd3dDevice->CreateDescriptorHeap(&d3dDescriptorHeapDesc, __uuidof(ID3D12DescriptorHeap), (void **)&m_pd3dCbvSrvDescriptorHeap);

	m_d3dCbvCPUDescriptorStartHandle = m_pd3dCbvSrvDescriptorHeap->GetCPUDescriptorHandleForHeapStart();
	m_d3dCbvGPUDescriptorStartHandle = m_pd3dCbvSrvDescriptorHeap->GetGPUDescriptorHandleForHeapStart();
	m_d3dSrvCPUDescriptorStartHandle.ptr = m_d3dCbvCPUDescriptorStartHandle.ptr + (::gnCbvSrvDescriptorIncrementSize * nConstantBufferViews);
	m_d3dSrvGPUDescriptorStartHandle.ptr = m_d3dCbvGPUDescriptorStartHandle.ptr + (::gnCbvSrvDescriptorIncrementSize * nConstantBufferViews);
}

void CShader::CreateConstantBufferViews(ID3D12Device *pd3dDevice, ID3D12GraphicsCommandList *pd3dCommandList, int nConstantBufferViews, ID3D12Resource *pd3dConstantBuffers, UINT nStride)
{
	D3D12_GPU_VIRTUAL_ADDRESS d3dGpuVirtualAddress = pd3dConstantBuffers->GetGPUVirtualAddress();
	D3D12_CONSTANT_BUFFER_VIEW_DESC d3dCBVDesc;
	d3dCBVDesc.SizeInBytes = nStride;
	for (int j = 0; j < nConstantBufferViews; j++)
	{
		d3dCBVDesc.BufferLocation = d3dGpuVirtualAddress + (nStride * j);
		D3D12_CPU_DESCRIPTOR_HANDLE d3dCbvCPUDescriptorHandle;
		d3dCbvCPUDescriptorHandle.ptr = m_d3dCbvCPUDescriptorStartHandle.ptr + (::gnCbvSrvDescriptorIncrementSize * j);
		pd3dDevice->CreateConstantBufferView(&d3dCBVDesc, d3dCbvCPUDescriptorHandle);
	}
}

D3D12_SHADER_RESOURCE_VIEW_DESC GetShaderResourceViewDesc(D3D12_RESOURCE_DESC d3dResourceDesc, UINT nTextureType)
{
	D3D12_SHADER_RESOURCE_VIEW_DESC d3dShaderResourceViewDesc;
	d3dShaderResourceViewDesc.Format = d3dResourceDesc.Format;
	d3dShaderResourceViewDesc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
	switch (nTextureType)
	{
	case RESOURCE_TEXTURE2D: //(d3dResourceDesc.Dimension == D3D12_RESOURCE_DIMENSION_TEXTURE2D)(d3dResourceDesc.DepthOrArraySize == 1)
	case RESOURCE_TEXTURE2D_ARRAY:
		d3dShaderResourceViewDesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2D;
		d3dShaderResourceViewDesc.Texture2D.MipLevels = -1;
		d3dShaderResourceViewDesc.Texture2D.MostDetailedMip = 0;
		d3dShaderResourceViewDesc.Texture2D.PlaneSlice = 0;
		d3dShaderResourceViewDesc.Texture2D.ResourceMinLODClamp = 0.0f;
		break;
	case RESOURCE_TEXTURE2DARRAY: //(d3dResourceDesc.Dimension == D3D12_RESOURCE_DIMENSION_TEXTURE2D)(d3dResourceDesc.DepthOrArraySize != 1)
		d3dShaderResourceViewDesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2DARRAY;
		d3dShaderResourceViewDesc.Texture2DArray.MipLevels = -1;
		d3dShaderResourceViewDesc.Texture2DArray.MostDetailedMip = 0;
		d3dShaderResourceViewDesc.Texture2DArray.PlaneSlice = 0;
		d3dShaderResourceViewDesc.Texture2DArray.ResourceMinLODClamp = 0.0f;
		d3dShaderResourceViewDesc.Texture2DArray.FirstArraySlice = 0;
		d3dShaderResourceViewDesc.Texture2DArray.ArraySize = d3dResourceDesc.DepthOrArraySize;
		break;
	case RESOURCE_TEXTURE_CUBE: //(d3dResourceDesc.Dimension == D3D12_RESOURCE_DIMENSION_TEXTURE2D)(d3dResourceDesc.DepthOrArraySize == 6)
		d3dShaderResourceViewDesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURECUBE;
		d3dShaderResourceViewDesc.TextureCube.MipLevels = -1;
		d3dShaderResourceViewDesc.TextureCube.MostDetailedMip = 0;
		d3dShaderResourceViewDesc.TextureCube.ResourceMinLODClamp = 0.0f;
		break;
	case RESOURCE_BUFFER: //(d3dResourceDesc.Dimension == D3D12_RESOURCE_DIMENSION_BUFFER)
		d3dShaderResourceViewDesc.ViewDimension = D3D12_SRV_DIMENSION_BUFFER;
		d3dShaderResourceViewDesc.Buffer.FirstElement = 0;
		d3dShaderResourceViewDesc.Buffer.NumElements = 0;
		d3dShaderResourceViewDesc.Buffer.StructureByteStride = 0;
		d3dShaderResourceViewDesc.Buffer.Flags = D3D12_BUFFER_SRV_FLAG_NONE;
		break;
	}
	return(d3dShaderResourceViewDesc);
}

void CShader::CreateShaderResourceViews(ID3D12Device *pd3dDevice, ID3D12GraphicsCommandList *pd3dCommandList, CTexture *pTexture, UINT nRootParameterStartIndex, bool bAutoIncrement)
{
	// 여기 주석친 이유는 지역변수로 접근하면 한개의 테이블에 집어넣은 여러개의 텍스처(빌보드)가 매번 초기화되어
	// 적용되니까 밑에 ptr을 디스크립터사이즈만큼 증가시켜 다음텍스처를 루트시그니처에 연결해야한다.
	// 같은 루트시그니처 파라미터를 쓰지만 서술자테이블에 해당 텍스처의 개수의 텍스처(srv)가 들어가 있음.
	/*D3D12_CPU_DESCRIPTOR_HANDLE d3dSrvCPUDescriptorHandle = m_d3dSrvCPUDescriptorStartHandle;
	D3D12_GPU_DESCRIPTOR_HANDLE d3dSrvGPUDescriptorHandle = m_d3dSrvGPUDescriptorStartHandle;*/
	int nTextures = pTexture->GetTextures();
	int nTextureType = pTexture->GetTextureType();
	for (int i = 0; i < nTextures; i++)
	{
		ID3D12Resource *pShaderResource = pTexture->GetTexture(i);
		D3D12_RESOURCE_DESC d3dResourceDesc = pShaderResource->GetDesc();
		D3D12_SHADER_RESOURCE_VIEW_DESC d3dShaderResourceViewDesc = GetShaderResourceViewDesc(d3dResourceDesc, nTextureType);
		pd3dDevice->CreateShaderResourceView(pShaderResource, &d3dShaderResourceViewDesc, m_d3dSrvCPUDescriptorStartHandle);
		m_d3dSrvCPUDescriptorStartHandle.ptr += ::gnCbvSrvDescriptorIncrementSize;

		// 해당 텍스처를 루트시그니처에 셋
		pTexture->SetRootArgument(i, (bAutoIncrement) ? (nRootParameterStartIndex + i) : nRootParameterStartIndex, m_d3dSrvGPUDescriptorStartHandle);
		m_d3dSrvGPUDescriptorStartHandle.ptr += ::gnCbvSrvDescriptorIncrementSize;
	}
}

void CShader::CreateShaderVariables(ID3D12Device *pd3dDevice, ID3D12GraphicsCommandList *pd3dCommandList)
{
}

void CShader::UpdateShaderVariables(ID3D12GraphicsCommandList *pd3dCommandList)
{
}

void CShader::UpdateShaderVariable(ID3D12GraphicsCommandList *pd3dCommandList, XMFLOAT4X4 *pxmf4x4World)
{
}

void CShader::ReleaseShaderVariables()
{
	if (m_pd3dCbvSrvDescriptorHeap) {
		m_pd3dCbvSrvDescriptorHeap->Release();
		m_pd3dCbvSrvDescriptorHeap = NULL;
	}
}

void CShader::ReleaseUploadBuffers()
{
}

void CShader::OnPrepareRender(ID3D12GraphicsCommandList *pd3dCommandList)
{
	if (m_ppd3dPipelineStates) pd3dCommandList->SetPipelineState(m_ppd3dPipelineStates[0]);
	pd3dCommandList->SetDescriptorHeaps(1, &m_pd3dCbvSrvDescriptorHeap);

	UpdateShaderVariables(pd3dCommandList);

}

void CShader::Render(ID3D12GraphicsCommandList *pd3dCommandList, CCamera *pCamera)
{
	OnPrepareRender(pd3dCommandList);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
CPlayerShader::CPlayerShader()
{
}

CPlayerShader::~CPlayerShader()
{
}

D3D12_INPUT_LAYOUT_DESC CPlayerShader::CreateInputLayout()
{
	UINT nInputElementDescs = 2;
	D3D12_INPUT_ELEMENT_DESC *pd3dInputElementDescs = new D3D12_INPUT_ELEMENT_DESC[nInputElementDescs];

	pd3dInputElementDescs[0] ={ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 };
	pd3dInputElementDescs[1] ={ "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 };

	D3D12_INPUT_LAYOUT_DESC d3dInputLayoutDesc;
	d3dInputLayoutDesc.pInputElementDescs = pd3dInputElementDescs;
	d3dInputLayoutDesc.NumElements = nInputElementDescs;

	return(d3dInputLayoutDesc);
}

D3D12_SHADER_BYTECODE CPlayerShader::CreateVertexShader(ID3DBlob **ppd3dShaderBlob)
{
	return(CShader::CompileShaderFromFile(L"Shaders.hlsl", "VSPlayer", "vs_5_1", ppd3dShaderBlob));
}

D3D12_SHADER_BYTECODE CPlayerShader::CreatePixelShader(ID3DBlob **ppd3dShaderBlob)
{
	return(CShader::CompileShaderFromFile(L"Shaders.hlsl", "PSPlayer", "ps_5_1", ppd3dShaderBlob));
}

void CPlayerShader::CreateShader(ID3D12Device *pd3dDevice, ID3D12RootSignature *pd3dGraphicsRootSignature, UINT nRenderTargets)
{
	m_nPipelineStates = 1;
	m_ppd3dPipelineStates = new ID3D12PipelineState*[m_nPipelineStates];
	CShader::CreateShader(pd3dDevice, pd3dGraphicsRootSignature, nRenderTargets);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
CTexturedShader::CTexturedShader()
{
}

CTexturedShader::~CTexturedShader()
{
}

D3D12_INPUT_LAYOUT_DESC CTexturedShader::CreateInputLayout()
{
	UINT nInputElementDescs = 2;
	D3D12_INPUT_ELEMENT_DESC *pd3dInputElementDescs = new D3D12_INPUT_ELEMENT_DESC[nInputElementDescs];

	pd3dInputElementDescs[0] ={ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 };
	pd3dInputElementDescs[1] ={ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 12, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 };

	D3D12_INPUT_LAYOUT_DESC d3dInputLayoutDesc;
	d3dInputLayoutDesc.pInputElementDescs = pd3dInputElementDescs;
	d3dInputLayoutDesc.NumElements = nInputElementDescs;

	return(d3dInputLayoutDesc);
}

D3D12_SHADER_BYTECODE CTexturedShader::CreateVertexShader(ID3DBlob **ppd3dShaderBlob)
{
	return(CShader::CompileShaderFromFile(L"Shaders.hlsl", "VSTextured", "vs_5_1", ppd3dShaderBlob));
}

D3D12_SHADER_BYTECODE CTexturedShader::CreatePixelShader(ID3DBlob **ppd3dShaderBlob)
{
	return(CShader::CompileShaderFromFile(L"Shaders.hlsl", "PSTextured", "ps_5_1", ppd3dShaderBlob));
}

void CTexturedShader::CreateShader(ID3D12Device *pd3dDevice, ID3D12RootSignature *pd3dGraphicsRootSignature, UINT nRenderTargets)
{
	m_nPipelineStates = 1;
	m_ppd3dPipelineStates = new ID3D12PipelineState*[m_nPipelineStates];
	CShader::CreateShader(pd3dDevice, pd3dGraphicsRootSignature, nRenderTargets);
}

/////////////////////////////////////////////////////////////////////////
// 빌보드 트리 셰이더(배열)

CBillboardTreeShader::CBillboardTreeShader()
{
}

CBillboardTreeShader::~CBillboardTreeShader()
{
}


D3D12_BLEND_DESC CBillboardTreeShader::CreateBlendState()
{
	D3D12_BLEND_DESC d3dBlendDesc;
	::ZeroMemory(&d3dBlendDesc, sizeof(D3D12_BLEND_DESC));
	d3dBlendDesc.AlphaToCoverageEnable = true;
	d3dBlendDesc.IndependentBlendEnable = FALSE;
	d3dBlendDesc.RenderTarget[0].BlendEnable = FALSE;
	d3dBlendDesc.RenderTarget[0].LogicOpEnable = FALSE;
	d3dBlendDesc.RenderTarget[0].SrcBlend = D3D12_BLEND_ONE;
	d3dBlendDesc.RenderTarget[0].DestBlend = D3D12_BLEND_ZERO;
	d3dBlendDesc.RenderTarget[0].BlendOp = D3D12_BLEND_OP_ADD;
	d3dBlendDesc.RenderTarget[0].SrcBlendAlpha = D3D12_BLEND_ONE;
	d3dBlendDesc.RenderTarget[0].DestBlendAlpha = D3D12_BLEND_ZERO;
	d3dBlendDesc.RenderTarget[0].BlendOpAlpha = D3D12_BLEND_OP_ADD;
	d3dBlendDesc.RenderTarget[0].LogicOp = D3D12_LOGIC_OP_NOOP;
	d3dBlendDesc.RenderTarget[0].RenderTargetWriteMask = D3D12_COLOR_WRITE_ENABLE_ALL;

	return(d3dBlendDesc);
}

void CBillboardTreeShader::CreateShaderVariables(ID3D12Device *pd3dDevice, ID3D12GraphicsCommandList *pd3dCommandList)
{
	UINT ncbElementBytes = ((sizeof(CB_GAMEOBJECT_INFO) + 255) & ~255); //256의 배수
	m_pd3dcbTreeGameObjects = ::CreateBufferResource(pd3dDevice, pd3dCommandList, NULL, ncbElementBytes * m_nTreeObjects, D3D12_HEAP_TYPE_UPLOAD, D3D12_RESOURCE_STATE_VERTEX_AND_CONSTANT_BUFFER, NULL);

	m_pd3dcbTreeGameObjects->Map(0, NULL, (void **)&m_pcbMappedTreeGameObjects);
}

void CBillboardTreeShader::UpdateShaderVariables(ID3D12GraphicsCommandList *pd3dCommandList)
{
	UINT ncbElementBytes = ((sizeof(CB_GAMEOBJECT_INFO) + 255) & ~255);
	for (int j = 0; j < m_nTreeObjects; j++)
	{
		CB_GAMEOBJECT_INFO *pbMappedcbTreeGameObject = (CB_GAMEOBJECT_INFO *)((UINT8 *)m_pcbMappedTreeGameObjects + (j * ncbElementBytes));
		XMStoreFloat4x4(&pbMappedcbTreeGameObject->m_xmf4x4World, XMMatrixTranspose(XMLoadFloat4x4(&m_ppTreeObjects[j]->m_xmf4x4World)));
	}
}

void CBillboardTreeShader::ReleaseShaderVariables()
{
	if (m_pd3dcbTreeGameObjects)
	{
		m_pd3dcbTreeGameObjects->Unmap(0, NULL);
		m_pd3dcbTreeGameObjects->Release();
	}

	CTexturedShader::ReleaseShaderVariables();
}

D3D12_SHADER_BYTECODE CBillboardTreeShader::CreateVertexShader(ID3DBlob **ppd3dShaderBlob)
{
	return(CShader::CompileShaderFromFile(L"Shaders.hlsl", "VSTree", "vs_5_1", ppd3dShaderBlob));
}

D3D12_SHADER_BYTECODE CBillboardTreeShader::CreatePixelShader(ID3DBlob **ppd3dShaderBlob)
{
	return(CShader::CompileShaderFromFile(L"Shaders.hlsl", "PSTree", "ps_5_1", ppd3dShaderBlob));
}

void CBillboardTreeShader::BuildObjects(ID3D12Device *pd3dDevice, ID3D12GraphicsCommandList *pd3dCommandList, void *pContext)
{
	CHeightMapTerrain *pTerrain = (CHeightMapTerrain *)pContext;
	//
	float fxPitch = 200.0f;
	float fzPitch = 200.0f;
	//
	float fTerrainWidth = pTerrain->GetWidth();
	float fTerrainLength = pTerrain->GetLength();
	//
	int xObjects = int(fTerrainWidth / fxPitch);	// x축으로 몇개를 그릴건지. 맵의 x축 끝까지 총 몇개.
	int zObjects = int(fTerrainLength / fzPitch);	// z축으로 몇개를 그릴건지.	맵의 z축 끝까지 총 몇개.

	m_nTreeObjects = (xObjects * zObjects);			// 맵 전체에 그릴 오브젝트 개수.
	// 텍스처 생성
	CTexture* pTexture;

	pTexture = new CTexture(5, RESOURCE_TEXTURE2D_ARRAY, 0);
	pTexture->LoadTextureFromFile(pd3dDevice, pd3dCommandList, L"Image/tree1.dds", 0);
	pTexture->LoadTextureFromFile(pd3dDevice, pd3dCommandList, L"Image/tree2.dds", 1);
	pTexture->LoadTextureFromFile(pd3dDevice, pd3dCommandList, L"Image/tree3.dds", 2);
	pTexture->LoadTextureFromFile(pd3dDevice, pd3dCommandList, L"Image/tree4.dds", 3);
	pTexture->LoadTextureFromFile(pd3dDevice, pd3dCommandList, L"Image/tree5.dds", 4);
	
	UINT ncbElementBytes = ((sizeof(CB_GAMEOBJECT_INFO) + 255) & ~255);

	CreateCbvAndSrvDescriptorHeaps(pd3dDevice, pd3dCommandList, m_nTreeObjects, 5);			// srv 5개. 텍스처 5개 쓰니깐.
	CreateShaderVariables(pd3dDevice, pd3dCommandList);
	CreateConstantBufferViews(pd3dDevice, pd3dCommandList, m_nTreeObjects, m_pd3dcbTreeGameObjects, ncbElementBytes);
	CreateShaderResourceViews(pd3dDevice, pd3dCommandList, pTexture, 6, false);

	// 재질 생성 후 텍스처 연결
	CMaterial *m_pMaterial = new CMaterial();
	m_pMaterial->SetTexture(pTexture);

	// 메시 생성
	CTexturedRectMesh *pRectMesh = new CTexturedRectMesh(pd3dDevice, pd3dCommandList, 50.0f, 70.0f, 0.0f, 0, 0, 0);

	// 객체 동적할당
	m_ppTreeObjects = new CBillboardObject*[m_nTreeObjects];

	CBillboardObject *pBillboardObject = NULL;
	float xPosition;
	float zPosition;
	for (int i = 0, x = 0; x < xObjects; x++)
	{
		for (int z = 0; z < zObjects; z++)
		{
			if (i % 2) {
				xPosition = x * fxPitch / 2 + 4;
				zPosition = z * fzPitch + 4;
			}
			xPosition = x * fxPitch / 2;		// 빌보드 생성할 때 x축으로 fxPitch만큼 떨어져있도록.
			zPosition = z * fzPitch;		// 빌보드 생성할 때 z축으로 fxPitch만큼 떨어져있도록.

			pBillboardObject = new CBillboardObject(1);

			pBillboardObject->SetMesh(0, pRectMesh);
			pBillboardObject->SetMaterial(m_pMaterial);
			float fHeight = pTerrain->GetHeight(xPosition, zPosition);
			pBillboardObject->SetPosition(xPosition, fHeight + 35.0f, zPosition);
			pBillboardObject->SetCbvGPUDescriptorHandlePtr(m_d3dCbvGPUDescriptorStartHandle.ptr + (::gnCbvSrvDescriptorIncrementSize * i));
			m_ppTreeObjects[i++] = pBillboardObject;
		}
	}
}

void CBillboardTreeShader::ReleaseObjects()
{
	if (m_ppTreeObjects) {
		for (int i = 0; i < m_nTreeObjects; ++i) {
			if (m_ppTreeObjects[i]) {
				delete m_ppTreeObjects[i];
				m_ppTreeObjects[i] = nullptr;
			}
		}
		delete[] m_ppTreeObjects;
	}
}

void CBillboardTreeShader::AnimateObjects(float fTimeElapsed)
{
	//for (int j = 0; j < m_nTreeObjects; j++)
	//{
	//	m_ppTreeObjects[j]->Animate(fTimeElapsed, m_pCamera);
	//}
}

void CBillboardTreeShader::ReleaseUploadBuffers()
{
	if (m_ppTreeObjects)
	{
		for (int j = 0; j < m_nTreeObjects; ++j) if (m_ppTreeObjects[j]) m_ppTreeObjects[j]->ReleaseUploadBuffers();
	}
}

void CBillboardTreeShader::Render(ID3D12GraphicsCommandList *pd3dCommandList, CCamera *pCamera)
{
	CTexturedShader::Render(pd3dCommandList, pCamera);

	XMFLOAT3 xmf3CameraPosition = pCamera->GetPosition();
	for (int j = 0; j < m_nTreeObjects; ++j)
	{
		if (m_ppTreeObjects[j]) {
			m_ppTreeObjects[j]->SetLookAt(xmf3CameraPosition, XMFLOAT3(0.0f, 1.0f, 0.0f));
			m_ppTreeObjects[j]->Render(pd3dCommandList, pCamera);
		}
	}
}

/////////////////////////////////////////////////////////////////////////
// 빌보드 트리 셰이더(Array)

//CBillboardTreeArrayShader::CBillboardTreeArrayShader()
//{
//}
//
//CBillboardTreeArrayShader::~CBillboardTreeArrayShader()
//{
//}
//
//
//D3D12_BLEND_DESC CBillboardTreeArrayShader::CreateBlendState()
//{
//	D3D12_BLEND_DESC d3dBlendDesc;
//	::ZeroMemory(&d3dBlendDesc, sizeof(D3D12_BLEND_DESC));
//	d3dBlendDesc.AlphaToCoverageEnable = true;
//	d3dBlendDesc.IndependentBlendEnable = FALSE;
//	d3dBlendDesc.RenderTarget[0].BlendEnable = FALSE;
//	d3dBlendDesc.RenderTarget[0].LogicOpEnable = FALSE;
//	d3dBlendDesc.RenderTarget[0].SrcBlend = D3D12_BLEND_ONE;
//	d3dBlendDesc.RenderTarget[0].DestBlend = D3D12_BLEND_ZERO;
//	d3dBlendDesc.RenderTarget[0].BlendOp = D3D12_BLEND_OP_ADD;
//	d3dBlendDesc.RenderTarget[0].SrcBlendAlpha = D3D12_BLEND_ONE;
//	d3dBlendDesc.RenderTarget[0].DestBlendAlpha = D3D12_BLEND_ZERO;
//	d3dBlendDesc.RenderTarget[0].BlendOpAlpha = D3D12_BLEND_OP_ADD;
//	d3dBlendDesc.RenderTarget[0].LogicOp = D3D12_LOGIC_OP_NOOP;
//	d3dBlendDesc.RenderTarget[0].RenderTargetWriteMask = D3D12_COLOR_WRITE_ENABLE_ALL;
//
//	return(d3dBlendDesc);
//}
//
//void CBillboardTreeArrayShader::CreateShaderVariables(ID3D12Device *pd3dDevice, ID3D12GraphicsCommandList *pd3dCommandList)
//{
//	UINT ncbElementBytes = ((sizeof(CB_GAMEOBJECT_INFO) + 255) & ~255); //256의 배수
//	m_pd3dcbTreeGameObjects = ::CreateBufferResource(pd3dDevice, pd3dCommandList, NULL, ncbElementBytes * m_nTreeObjects, D3D12_HEAP_TYPE_UPLOAD, D3D12_RESOURCE_STATE_VERTEX_AND_CONSTANT_BUFFER, NULL);
//
//	m_pd3dcbTreeGameObjects->Map(0, NULL, (void **)&m_pcbMappedTreeGameObjects);
//}
//
//void CBillboardTreeArrayShader::UpdateShaderVariables(ID3D12GraphicsCommandList *pd3dCommandList)
//{
//	UINT ncbElementBytes = ((sizeof(CB_GAMEOBJECT_INFO) + 255) & ~255);
//	for (int j = 0; j < m_nTreeObjects; j++)
//	{
//		CB_GAMEOBJECT_INFO *pbMappedcbTreeGameObject = (CB_GAMEOBJECT_INFO *)((UINT8 *)m_pcbMappedTreeGameObjects + (j * ncbElementBytes));
//		XMStoreFloat4x4(&pbMappedcbTreeGameObject->m_xmf4x4World, XMMatrixTranspose(XMLoadFloat4x4(&m_ppTreeObjects[j]->m_xmf4x4World)));
//	}
//}
//
//void CBillboardTreeArrayShader::ReleaseShaderVariables()
//{
//	if (m_pd3dcbTreeGameObjects)
//	{
//		m_pd3dcbTreeGameObjects->Unmap(0, NULL);
//		m_pd3dcbTreeGameObjects->Release();
//	}
//
//	CTexturedShader::ReleaseShaderVariables();
//}
//
//D3D12_SHADER_BYTECODE CBillboardTreeArrayShader::CreateVertexShader(ID3DBlob **ppd3dShaderBlob)
//{
//	return(CShader::CompileShaderFromFile(L"Shaders.hlsl", "VSTreeArray", "vs_5_1", ppd3dShaderBlob));
//}
//
//D3D12_SHADER_BYTECODE CBillboardTreeArrayShader::CreatePixelShader(ID3DBlob **ppd3dShaderBlob)
//{
//	return(CShader::CompileShaderFromFile(L"Shaders.hlsl", "PSTreeArray", "ps_5_1", ppd3dShaderBlob));
//}
//
//void CBillboardTreeArrayShader::BuildObjects(ID3D12Device *pd3dDevice, ID3D12GraphicsCommandList *pd3dCommandList, void *pContext)
//{
//	CHeightMapTerrain *pTerrain = (CHeightMapTerrain *)pContext;
//	//
//	float fxPitch = 200.0f;
//	float fzPitch = 200.0f;
//	//
//	float fTerrainWidth = pTerrain->GetWidth();
//	float fTerrainLength = pTerrain->GetLength();
//	//
//	int xObjects = int(fTerrainWidth / fxPitch);	// x축으로 몇개를 그릴건지. 맵의 x축 끝까지 총 몇개.
//	int zObjects = int(fTerrainLength / fzPitch);	// z축으로 몇개를 그릴건지.	맵의 z축 끝까지 총 몇개.
//
//	m_nTreeObjects = (xObjects * zObjects);			// 맵 전체에 그릴 오브젝트 개수.
//	cout << m_nTreeObjects << endl;
//	// 텍스처 생성
//	CTexture* pTexture;
//
//	pTexture = new CTexture(1, RESOURCE_TEXTURE2DARRAY, 0);
//	pTexture->LoadTextureFromFile(pd3dDevice, pd3dCommandList, L"Image/treearray.dds", 0);
//	
//
//	UINT ncbElementBytes = ((sizeof(CB_GAMEOBJECT_INFO) + 255) & ~255);
//
//	CreateCbvAndSrvDescriptorHeaps(pd3dDevice, pd3dCommandList, m_nTreeObjects, 1);	// srv 1개. 텍스처 1개 쓰니깐.
//	CreateShaderVariables(pd3dDevice, pd3dCommandList);
//	CreateConstantBufferViews(pd3dDevice, pd3dCommandList, m_nTreeObjects, m_pd3dcbTreeGameObjects, ncbElementBytes);
//	CreateShaderResourceViews(pd3dDevice, pd3dCommandList, pTexture, 7, true);
//
//	// 재질 생성 후 텍스처 연결
//	CMaterial *m_pMaterial = new CMaterial();
//	m_pMaterial->SetTexture(pTexture);
//
//	// 메시 생성
//	CTexturedRectMesh *pRectMesh = new CTexturedRectMesh(pd3dDevice, pd3dCommandList, 50.0f, 70.0f, 0.0f, 0, 0, 0);
//
//	// 객체 동적할당
//	m_ppTreeObjects = new CBillboardObject*[m_nTreeObjects];
//
//	CBillboardObject *pBillboardObject = NULL;
//	float xPosition;
//	float zPosition;
//	for (int i = 0, x = xObjects; x < xObjects*2; x++)
//	{
//		for (int z = 0; z < zObjects; z++)
//		{
//			if (i % 2) {
//				xPosition = x * fxPitch / 2 + 4;
//				zPosition = z * fzPitch + 4;
//			}
//			xPosition = x * fxPitch / 2;		// 빌보드 생성할 때 x축으로 fxPitch만큼 떨어져있도록.
//			zPosition = z * fzPitch;		// 빌보드 생성할 때 z축으로 fxPitch만큼 떨어져있도록.
//
//			pBillboardObject = new CBillboardObject(1);
//
//			pBillboardObject->SetMesh(0, pRectMesh);
//			pBillboardObject->SetMaterial(m_pMaterial);
//			float fHeight = pTerrain->GetHeight(xPosition, zPosition);
//			pBillboardObject->SetPosition(xPosition, fHeight + 30.0f, zPosition);
//			pBillboardObject->SetCbvGPUDescriptorHandlePtr(m_d3dCbvGPUDescriptorStartHandle.ptr + (::gnCbvSrvDescriptorIncrementSize * i));
//			m_ppTreeObjects[i++] = pBillboardObject;
//		}
//	}
//}
//
//void CBillboardTreeArrayShader::ReleaseObjects()
//{
//	if (m_ppTreeObjects) {
//		for (int i = 0; i < m_nTreeObjects; ++i) {
//			if (m_ppTreeObjects[i]) {
//				delete m_ppTreeObjects[i];
//				m_ppTreeObjects[i] = nullptr;
//			}
//		}
//		delete[] m_ppTreeObjects;
//	}
//}
//
//void CBillboardTreeArrayShader::AnimateObjects(float fTimeElapsed)
//{
//	//for (int j = 0; j < m_nTreeObjects; j++)
//	//{
//	//	m_ppTreeObjects[j]->Animate(fTimeElapsed, m_pCamera);
//	//}
//}
//
//void CBillboardTreeArrayShader::ReleaseUploadBuffers()
//{
//	if (m_ppTreeObjects)
//	{
//		for (int j = 0; j < m_nTreeObjects; ++j) if (m_ppTreeObjects[j]) m_ppTreeObjects[j]->ReleaseUploadBuffers();
//	}
//}
//
//void CBillboardTreeArrayShader::Render(ID3D12GraphicsCommandList *pd3dCommandList, CCamera *pCamera)
//{
//	CTexturedShader::Render(pd3dCommandList, pCamera);
//
//	XMFLOAT3 xmf3CameraPosition = pCamera->GetPosition();
//	for (int j = 0; j < m_nTreeObjects; ++j)
//	{
//		if (m_ppTreeObjects[j]) {
//			m_ppTreeObjects[j]->SetLookAt(xmf3CameraPosition, XMFLOAT3(0.0f, 1.0f, 0.0f));
//			m_ppTreeObjects[j]->Render(pd3dCommandList, pCamera);
//		}
//	}
//}

///////////////////////////////////////////////////////////////////////
CGeometryBillboardTreeShader::CGeometryBillboardTreeShader()
{
}

CGeometryBillboardTreeShader::~CGeometryBillboardTreeShader()
{
	ReleaseShaderVariables();
	ReleaseUploadBuffers();
}

void CGeometryBillboardTreeShader::CreateShaderResourceViews(ID3D12Device *pd3dDevice, ID3D12GraphicsCommandList *pd3dCommandList, CTexture *pTexture, UINT nRootParameterStartIndex, bool bAutoIncrement)
{
	// 여기 주석친 이유는 지역변수로 접근하면 한개의 테이블에 집어넣은 여러개의 텍스처(빌보드)가 매번 초기화되어
	// 적용되니까 밑에 ptr을 디스크립터사이즈만큼 증가시켜 다음텍스처를 루트시그니처에 연결해야한다.
	// 같은 루트시그니처 파라미터를 쓰지만 서술자테이블에 해당 텍스처의 개수의 텍스처(srv)가 들어가 있음.
	// D3D12_CPU_DESCRIPTOR_HANDLE d3dSrvCPUDescriptorHandle = m_d3dSrvCPUDescriptorStartHandle;
	// D3D12_GPU_DESCRIPTOR_HANDLE d3dSrvGPUDescriptorHandle = m_d3dSrvGPUDescriptorStartHandle;
	int nTextures = pTexture->GetTextures();

	int nTextureType = pTexture->GetTextureType();
	for (int i = 0; i < nTextures; i++)
	{
		ID3D12Resource *pShaderResource = pTexture->GetTexture(i);
		D3D12_RESOURCE_DESC d3dResourceDesc = pShaderResource->GetDesc();
		D3D12_SHADER_RESOURCE_VIEW_DESC d3dShaderResourceViewDesc = GetShaderResourceViewDesc(d3dResourceDesc, nTextureType);
		pd3dDevice->CreateShaderResourceView(pShaderResource, &d3dShaderResourceViewDesc, m_d3dSrvCPUDescriptorStartHandle);
		m_d3dSrvCPUDescriptorStartHandle.ptr += ::gnCbvSrvDescriptorIncrementSize;
		// 해당 텍스처를 루트시그니처에 셋
		pTexture->SetRootArgument(i, (bAutoIncrement) ? (nRootParameterStartIndex + i) : nRootParameterStartIndex, m_d3dSrvGPUDescriptorStartHandle);
		m_d3dSrvGPUDescriptorStartHandle.ptr += ::gnCbvSrvDescriptorIncrementSize;
	}
}

D3D12_BLEND_DESC CGeometryBillboardTreeShader::CreateBlendState()
{
	D3D12_BLEND_DESC d3dBlendDesc;
	::ZeroMemory(&d3dBlendDesc, sizeof(D3D12_BLEND_DESC));
	d3dBlendDesc.AlphaToCoverageEnable = true;
	d3dBlendDesc.IndependentBlendEnable = FALSE;
	d3dBlendDesc.RenderTarget[0].BlendEnable = FALSE;
	d3dBlendDesc.RenderTarget[0].LogicOpEnable = FALSE;
	d3dBlendDesc.RenderTarget[0].SrcBlend = D3D12_BLEND_SRC_ALPHA;
	d3dBlendDesc.RenderTarget[0].DestBlend = D3D12_BLEND_INV_SRC_ALPHA;
	d3dBlendDesc.RenderTarget[0].BlendOp = D3D12_BLEND_OP_ADD;
	d3dBlendDesc.RenderTarget[0].SrcBlendAlpha = D3D12_BLEND_ONE;
	d3dBlendDesc.RenderTarget[0].DestBlendAlpha = D3D12_BLEND_ZERO;
	d3dBlendDesc.RenderTarget[0].BlendOpAlpha = D3D12_BLEND_OP_ADD;
	d3dBlendDesc.RenderTarget[0].LogicOp = D3D12_LOGIC_OP_NOOP;
	d3dBlendDesc.RenderTarget[0].RenderTargetWriteMask = D3D12_COLOR_WRITE_ENABLE_ALL;
	return(d3dBlendDesc);
}

D3D12_INPUT_LAYOUT_DESC CGeometryBillboardTreeShader::CreateInputLayout()
{
	UINT nInputElementDescs = 2;
	D3D12_INPUT_ELEMENT_DESC *pd3dInputElementDescs = new D3D12_INPUT_ELEMENT_DESC[nInputElementDescs];

	pd3dInputElementDescs[0] = { "POSITION",0,DXGI_FORMAT_R32G32B32_FLOAT,0,0,D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA,0 };
	pd3dInputElementDescs[1] = { "SIZE",0,DXGI_FORMAT_R32G32_FLOAT,0,12,D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA,0 };

	D3D12_INPUT_LAYOUT_DESC d3dInputLayoutDesc;
	d3dInputLayoutDesc.pInputElementDescs = pd3dInputElementDescs;
	d3dInputLayoutDesc.NumElements = nInputElementDescs;

	return(d3dInputLayoutDesc);
}

D3D12_SHADER_BYTECODE CGeometryBillboardTreeShader::CreateVertexShader(ID3DBlob **ppd3dShaderBlob)
{
	return(CShader::CompileShaderFromFile(L"Shaders.hlsl", "VS_Geometry", "vs_5_1", ppd3dShaderBlob));
}

D3D12_SHADER_BYTECODE CGeometryBillboardTreeShader::CreateGeometryShader(ID3DBlob **ppd3dShaderBlob)
{
	return(CShader::CompileShaderFromFile(L"Shaders.hlsl", "GS", "gs_5_1", ppd3dShaderBlob));
}

D3D12_SHADER_BYTECODE CGeometryBillboardTreeShader::CreatePixelShader(ID3DBlob **ppd3dShaderBlob)
{
	return(CShader::CompileShaderFromFile(L"Shaders.hlsl", "PS_Geometry", "ps_5_1", ppd3dShaderBlob));
}

void CGeometryBillboardTreeShader::CreateShader(ID3D12Device *pd3dDevice, ID3D12RootSignature *pd3dGraphicsRootSignature)
{
	m_nPipelineStates = 1;
	m_ppd3dPipelineStates = new ID3D12PipelineState*[m_nPipelineStates];

	ID3DBlob *pd3dVertexShaderBlob = NULL, *pd3dPixelShaderBlob = NULL;
	ID3DBlob *pd3dGeometeryShaderBlob = NULL;

	D3D12_GRAPHICS_PIPELINE_STATE_DESC d3dPipelineStateDesc;
	::ZeroMemory(&d3dPipelineStateDesc, sizeof(D3D12_GRAPHICS_PIPELINE_STATE_DESC));
	d3dPipelineStateDesc.pRootSignature = pd3dGraphicsRootSignature;
	d3dPipelineStateDesc.VS = CreateVertexShader(&pd3dVertexShaderBlob);			//계층 구조 상에서 오버라이딩 가능 
	d3dPipelineStateDesc.PS = CreatePixelShader(&pd3dPixelShaderBlob);				//계층 구조 상에서 오버라이딩 가능
	d3dPipelineStateDesc.GS = CreateGeometryShader(&pd3dGeometeryShaderBlob);
	d3dPipelineStateDesc.RasterizerState = CreateRasterizerState();
	d3dPipelineStateDesc.BlendState = CreateBlendState();
	d3dPipelineStateDesc.DepthStencilState = CreateDepthStencilState();
	d3dPipelineStateDesc.InputLayout = CreateInputLayout();							//계층구조상에서 오버이딩 가능
	d3dPipelineStateDesc.SampleMask = UINT_MAX;
	d3dPipelineStateDesc.PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_POINT;
	d3dPipelineStateDesc.NumRenderTargets = 1;
	d3dPipelineStateDesc.RTVFormats[0] = DXGI_FORMAT_R8G8B8A8_UNORM;
	d3dPipelineStateDesc.DSVFormat = DXGI_FORMAT_D24_UNORM_S8_UINT;
	d3dPipelineStateDesc.SampleDesc.Count = 1;
	d3dPipelineStateDesc.Flags = D3D12_PIPELINE_STATE_FLAG_NONE;
	HRESULT hResult = pd3dDevice->CreateGraphicsPipelineState(&d3dPipelineStateDesc, __uuidof(ID3D12PipelineState), (void **)&m_ppd3dPipelineStates[0]);

	if (pd3dVertexShaderBlob) pd3dVertexShaderBlob->Release();
	if (pd3dPixelShaderBlob) pd3dPixelShaderBlob->Release();
	if (pd3dGeometeryShaderBlob) pd3dGeometeryShaderBlob->Release();

	if (d3dPipelineStateDesc.InputLayout.pInputElementDescs) delete[] d3dPipelineStateDesc.InputLayout.pInputElementDescs;

}

void CGeometryBillboardTreeShader::BuildObjects(ID3D12Device *pd3dDevice, ID3D12GraphicsCommandList *pd3dCommandList, void *pContext, int Batch[][257])
{
	CTexture* pTreeTexture = new CTexture(1, RESOURCE_TEXTURE2DARRAY, 0);
	pTreeTexture->LoadTextureFromFile(pd3dDevice, pd3dCommandList, L"Image/treearray.dds", 0);
	CreateCbvAndSrvDescriptorHeaps(pd3dDevice, pd3dCommandList, 0, 1);
	CreateShaderResourceViews(pd3dDevice, pd3dCommandList, pTreeTexture, 7, true);

	// 재질 생성 후 텍스처 연결
	m_pMaterial = new CMaterial();
	m_pMaterial->SetTexture(pTreeTexture);
	CHeightMapTerrain *pTerrain = (CHeightMapTerrain *)pContext;
	//
	float fxPitch = 200.0f;
	float fzPitch = 200.0f;
	//
	int fTerrainWidth = int(pTerrain->GetWidth());
	int fTerrainLength = int(pTerrain->GetLength());
	//
	int xObjects = int(fTerrainWidth / fxPitch);	// x축으로 몇개를 그릴건지. 맵의 x축 끝까지 총 몇개.
	int zObjects = int(fTerrainLength / fzPitch);	// z축으로 몇개를 그릴건지.	맵의 z축 끝까지 총 몇개.

	m_nVertices = (xObjects * zObjects);			// 맵 전체에 그릴 오브젝트 개수.
	m_nStride = sizeof(CBillboardVertex);
	XMFLOAT3 xmf3Position;

	CBillboardVertex *pTreeVertices = new CBillboardVertex[m_nVertices];

	for (int i = 0; i < m_nVertices;) {
		xmf3Position.x = 1000 + (int)(i * fxPitch / 2) % 1000;
		xmf3Position.z = (int)(i / 10 * fzPitch) % 2100;
		float fHeight = pTerrain->GetHeight(xmf3Position.x, xmf3Position.z);
		xmf3Position.y = fHeight + 30;
		pTreeVertices[i++] = CBillboardVertex(xmf3Position, XMFLOAT2(50, 70));
	}

	m_pd3dVertexBuffer = ::CreateBufferResource(pd3dDevice, pd3dCommandList, pTreeVertices,
		m_nStride*m_nVertices, D3D12_HEAP_TYPE_DEFAULT,
		D3D12_RESOURCE_STATE_VERTEX_AND_CONSTANT_BUFFER, &m_pd3dVertexUploadBuffer);

	m_pd3dVertexBufferView.BufferLocation = m_pd3dVertexBuffer->GetGPUVirtualAddress();
	m_pd3dVertexBufferView.StrideInBytes = m_nStride;
	m_pd3dVertexBufferView.SizeInBytes = m_nStride * m_nVertices;
	if (pTreeVertices) delete[] pTreeVertices;
}

void CGeometryBillboardTreeShader::CreateShaderVariables(ID3D12Device *pd3dDevice, ID3D12GraphicsCommandList *pd3dCommandList)
{
}

void CGeometryBillboardTreeShader::UpdateShaderVariables(ID3D12GraphicsCommandList *pd3dCommandList)
{
}

void CGeometryBillboardTreeShader::ReleaseShaderVariables()
{
	if (m_pd3dVertexBuffer)
		m_pd3dVertexBuffer->Release();
	m_pd3dVertexBuffer = nullptr;
}

void CGeometryBillboardTreeShader::ReleaseUploadBuffers()
{
	if (m_pd3dVertexUploadBuffer) m_pd3dVertexUploadBuffer->Release();
	m_pd3dVertexUploadBuffer = nullptr;
}

void CGeometryBillboardTreeShader::OnPrepareRender(ID3D12GraphicsCommandList *pd3dCommandList)
{
	if (m_ppd3dPipelineStates) pd3dCommandList->SetPipelineState(m_ppd3dPipelineStates[0]);
	pd3dCommandList->SetDescriptorHeaps(1, &m_pd3dCbvSrvDescriptorHeap);

	UpdateShaderVariables(pd3dCommandList);
}

void CGeometryBillboardTreeShader::Render(ID3D12GraphicsCommandList *pd3dCommandList, CCamera *pCamera)
{

	OnPrepareRender(pd3dCommandList);

	if (m_pMaterial)
	{
		if (m_pMaterial->m_pShader)
		{
			m_pMaterial->m_pShader->Render(pd3dCommandList, pCamera);
			m_pMaterial->m_pShader->UpdateShaderVariables(pd3dCommandList);

			UpdateShaderVariables(pd3dCommandList);
		}
		if (m_pMaterial->m_pTexture)
		{
			m_pMaterial->m_pTexture->UpdateShaderVariables(pd3dCommandList);
		}
	}

	pd3dCommandList->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_POINTLIST);

	pd3dCommandList->IASetVertexBuffers(0, 1, &m_pd3dVertexBufferView);

	pd3dCommandList->DrawInstanced(m_nVertices, 1, 0, 0);
	
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
CTerrainShader::CTerrainShader()
{
}

CTerrainShader::~CTerrainShader()
{
}

D3D12_INPUT_LAYOUT_DESC CTerrainShader::CreateInputLayout()
{
	UINT nInputElementDescs = 4;
	D3D12_INPUT_ELEMENT_DESC *pd3dInputElementDescs = new D3D12_INPUT_ELEMENT_DESC[nInputElementDescs];

	pd3dInputElementDescs[0] ={ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 };
	pd3dInputElementDescs[1] ={ "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 };
	pd3dInputElementDescs[2] ={ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 28, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 };
	pd3dInputElementDescs[3] = { "TEXCOORD", 1, DXGI_FORMAT_R32G32_FLOAT, 0, 36, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 };
	
	D3D12_INPUT_LAYOUT_DESC d3dInputLayoutDesc;
	d3dInputLayoutDesc.pInputElementDescs = pd3dInputElementDescs;
	d3dInputLayoutDesc.NumElements = nInputElementDescs;

	return(d3dInputLayoutDesc);
}

D3D12_SHADER_BYTECODE CTerrainShader::CreateVertexShader(ID3DBlob **ppd3dShaderBlob)
{
	return(CShader::CompileShaderFromFile(L"Shaders.hlsl", "VSTerrain", "vs_5_1", ppd3dShaderBlob));
}

D3D12_SHADER_BYTECODE CTerrainShader::CreatePixelShader(ID3DBlob **ppd3dShaderBlob)
{
	return(CShader::CompileShaderFromFile(L"Shaders.hlsl", "PSTerrain", "ps_5_1", ppd3dShaderBlob));
}

void CTerrainShader::CreateShader(ID3D12Device *pd3dDevice, ID3D12RootSignature *pd3dGraphicsRootSignature, UINT nRenderTargets)
{
	m_nPipelineStates = 1;
	m_ppd3dPipelineStates = new ID3D12PipelineState*[m_nPipelineStates];
	CShader::CreateShader(pd3dDevice, pd3dGraphicsRootSignature, nRenderTargets);
}

CPostProcessingShader::CPostProcessingShader()
{
}

CPostProcessingShader::~CPostProcessingShader()
{
	ReleaseShaderVariables();
	ReleaseObjects();
}

D3D12_DEPTH_STENCIL_DESC CPostProcessingShader::CreateDepthStencilState()
{
	D3D12_DEPTH_STENCIL_DESC d3dDepthStencilDesc;
	::ZeroMemory(&d3dDepthStencilDesc, sizeof(D3D12_DEPTH_STENCIL_DESC));
	d3dDepthStencilDesc.DepthEnable = FALSE;
	d3dDepthStencilDesc.DepthWriteMask = D3D12_DEPTH_WRITE_MASK_ALL;
	d3dDepthStencilDesc.DepthFunc = D3D12_COMPARISON_FUNC_ALWAYS;
	d3dDepthStencilDesc.StencilEnable = FALSE;
	d3dDepthStencilDesc.StencilReadMask = 0x00;
	d3dDepthStencilDesc.StencilWriteMask = 0x00;
	d3dDepthStencilDesc.FrontFace.StencilFailOp = D3D12_STENCIL_OP_KEEP;
	d3dDepthStencilDesc.FrontFace.StencilDepthFailOp = D3D12_STENCIL_OP_KEEP;
	d3dDepthStencilDesc.FrontFace.StencilPassOp = D3D12_STENCIL_OP_KEEP;
	d3dDepthStencilDesc.FrontFace.StencilFunc = D3D12_COMPARISON_FUNC_NEVER;
	d3dDepthStencilDesc.BackFace.StencilFailOp = D3D12_STENCIL_OP_KEEP;
	d3dDepthStencilDesc.BackFace.StencilDepthFailOp = D3D12_STENCIL_OP_KEEP;
	d3dDepthStencilDesc.BackFace.StencilPassOp = D3D12_STENCIL_OP_KEEP;
	d3dDepthStencilDesc.BackFace.StencilFunc = D3D12_COMPARISON_FUNC_NEVER;

	return(d3dDepthStencilDesc);
}

D3D12_INPUT_LAYOUT_DESC CPostProcessingShader::CreateInputLayout()
{
	D3D12_INPUT_LAYOUT_DESC d3dInputLayoutDesc;
	d3dInputLayoutDesc.pInputElementDescs = NULL;
	d3dInputLayoutDesc.NumElements = 0;

	return(d3dInputLayoutDesc);
}


D3D12_SHADER_BYTECODE CPostProcessingShader::CreateVertexShader(ID3DBlob **ppd3dShaderBlob)
{
	return(CShader::CompileShaderFromFile(L"Shaders.hlsl", "VSPostProcessing", "vs_5_1", ppd3dShaderBlob));
}

D3D12_SHADER_BYTECODE CPostProcessingShader::CreatePixelShader(ID3DBlob **ppd3dShaderBlob)
{
	return(CShader::CompileShaderFromFile(L"Shaders.hlsl", "PSPostProcessing", "ps_5_1", ppd3dShaderBlob));
}

void CPostProcessingShader::CreateShader(ID3D12Device *pd3dDevice, ID3D12RootSignature *pd3dGraphicsRootSignature, UINT nRenderTargets)
{
	m_nPipelineStates = 1;
	m_ppd3dPipelineStates = new ID3D12PipelineState*[m_nPipelineStates];
	
	CShader::CreateShader(pd3dDevice, pd3dGraphicsRootSignature, nRenderTargets);
}

void CPostProcessingShader::BuildObjects(ID3D12Device *pd3dDevice, ID3D12GraphicsCommandList *pd3dCommandList, void *pContext)
{
	m_pTexture = (CTexture *)pContext;

	CreateCbvAndSrvDescriptorHeaps(pd3dDevice, pd3dCommandList, 0, m_pTexture->GetTextures());
	CreateShaderVariables(pd3dDevice, pd3dCommandList);
	CreateShaderResourceViews(pd3dDevice, pd3dCommandList, m_pTexture, 8, false);
}

void CPostProcessingShader::ReleaseObjects()
{
	if (m_pTexture) m_pTexture->Release();
}

void CPostProcessingShader::Render(ID3D12GraphicsCommandList *pd3dCommandList, CCamera *pCamera)
{
	pCamera->SetViewportsAndScissorRects(pd3dCommandList);

	CShader::Render(pd3dCommandList, pCamera);

	if (m_pTexture) m_pTexture->UpdateShaderVariables(pd3dCommandList);

	pd3dCommandList->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	pd3dCommandList->DrawInstanced(6, 1, 0, 0);
}


