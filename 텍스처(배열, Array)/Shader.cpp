//-----------------------------------------------------------------------------
// File: Shader.cpp
//-----------------------------------------------------------------------------

#include "stdafx.h"
#include "Shader.h"
#include "DDSTextureLoader12.h"

CShader::CShader()
{
	m_d3dSrvCPUDescriptorStartHandle.ptr = NULL;
	m_d3dSrvGPUDescriptorStartHandle.ptr = NULL;
}

CShader::~CShader()
{
	if (m_pd3dPipelineState) m_pd3dPipelineState->Release();
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

void CShader::CreateShader(ID3D12Device *pd3dDevice, ID3D12RootSignature *pd3dGraphicsRootSignature)
{
	ID3DBlob *pd3dVertexShaderBlob = NULL, *pd3dPixelShaderBlob = NULL;

	D3D12_GRAPHICS_PIPELINE_STATE_DESC d3dPipelineStateDesc;
	::ZeroMemory(&d3dPipelineStateDesc, sizeof(D3D12_GRAPHICS_PIPELINE_STATE_DESC));
	d3dPipelineStateDesc.pRootSignature = pd3dGraphicsRootSignature;
	d3dPipelineStateDesc.VS = CreateVertexShader(&pd3dVertexShaderBlob);
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
	HRESULT hResult = pd3dDevice->CreateGraphicsPipelineState(&d3dPipelineStateDesc, __uuidof(ID3D12PipelineState), (void **)&m_pd3dPipelineState);

	if (pd3dVertexShaderBlob) pd3dVertexShaderBlob->Release();
	if (pd3dPixelShaderBlob) pd3dPixelShaderBlob->Release();

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
	// ���� �ּ�ģ ������ ���������� �����ϸ� �Ѱ��� ���̺� ������� �������� �ؽ�ó(������)�� �Ź� �ʱ�ȭ�Ǿ�
	// ����Ǵϱ� �ؿ� ptr�� ��ũ���ͻ����ŭ �������� �����ؽ�ó�� ��Ʈ�ñ״�ó�� �����ؾ��Ѵ�.
	// ���� ��Ʈ�ñ״�ó �Ķ���͸� ������ ���������̺� �ش� �ؽ�ó�� ������ �ؽ�ó(srv)�� �� ����.
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

		// �ش� �ؽ�ó�� ��Ʈ�ñ״�ó�� ��
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
	if (m_pd3dCbvSrvDescriptorHeap) m_pd3dCbvSrvDescriptorHeap->Release();
}

void CShader::ReleaseUploadBuffers()
{
}

void CShader::OnPrepareRender(ID3D12GraphicsCommandList *pd3dCommandList)
{
	if (m_pd3dPipelineState) pd3dCommandList->SetPipelineState(m_pd3dPipelineState);
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

void CPlayerShader::CreateShader(ID3D12Device *pd3dDevice, ID3D12RootSignature *pd3dGraphicsRootSignature)
{
	CShader::CreateShader(pd3dDevice, pd3dGraphicsRootSignature);
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

void CTexturedShader::CreateShader(ID3D12Device *pd3dDevice, ID3D12RootSignature *pd3dGraphicsRootSignature)
{
	CShader::CreateShader(pd3dDevice, pd3dGraphicsRootSignature);
}

/////////////////////////////////////////////////////////////////////////
// ������ Ʈ�� ���̴�(�迭)

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
	UINT ncbElementBytes = ((sizeof(CB_GAMEOBJECT_INFO) + 255) & ~255); //256�� ���
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
	int xObjects = int(fTerrainWidth / fxPitch);	// x������ ��� �׸�����. ���� x�� ������ �� �.
	int zObjects = int(fTerrainLength / fzPitch);	// z������ ��� �׸�����.	���� z�� ������ �� �.

	m_nTreeObjects = (xObjects * zObjects);			// �� ��ü�� �׸� ������Ʈ ����.
	cout << m_nTreeObjects << endl;
	// �ؽ�ó ����
	CTexture* pTexture;

	pTexture = new CTexture(5, RESOURCE_TEXTURE2D_ARRAY, 0);
	pTexture->LoadTextureFromFile(pd3dDevice, pd3dCommandList, L"Image/tree1.dds", 0);
	pTexture->LoadTextureFromFile(pd3dDevice, pd3dCommandList, L"Image/tree2.dds", 1);
	pTexture->LoadTextureFromFile(pd3dDevice, pd3dCommandList, L"Image/tree3.dds", 2);
	pTexture->LoadTextureFromFile(pd3dDevice, pd3dCommandList, L"Image/tree4.dds", 3);
	pTexture->LoadTextureFromFile(pd3dDevice, pd3dCommandList, L"Image/tree5.dds", 4);
	
	UINT ncbElementBytes = ((sizeof(CB_GAMEOBJECT_INFO) + 255) & ~255);

	CreateCbvAndSrvDescriptorHeaps(pd3dDevice, pd3dCommandList, m_nTreeObjects, 5);			// srv 5��. �ؽ�ó 5�� ���ϱ�.
	CreateShaderVariables(pd3dDevice, pd3dCommandList);
	CreateConstantBufferViews(pd3dDevice, pd3dCommandList, m_nTreeObjects, m_pd3dcbTreeGameObjects, ncbElementBytes);
	CreateShaderResourceViews(pd3dDevice, pd3dCommandList, pTexture, 6, false);

	// ���� ���� �� �ؽ�ó ����
	CMaterial *m_pMaterial = new CMaterial();
	m_pMaterial->SetTexture(pTexture);

	// �޽� ����
	CTexturedRectMesh *pRectMesh = new CTexturedRectMesh(pd3dDevice, pd3dCommandList, 50.0f, 70.0f, 0.0f, 0, 0, 0);

	// ��ü �����Ҵ�
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
			xPosition = x * fxPitch / 2;		// ������ ������ �� x������ fxPitch��ŭ �������ֵ���.
			zPosition = z * fzPitch;		// ������ ������ �� z������ fxPitch��ŭ �������ֵ���.

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
// ������ Ʈ�� ���̴�(Array)

CBillboardTreeArrayShader::CBillboardTreeArrayShader()
{
}

CBillboardTreeArrayShader::~CBillboardTreeArrayShader()
{
}


D3D12_BLEND_DESC CBillboardTreeArrayShader::CreateBlendState()
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

void CBillboardTreeArrayShader::CreateShaderVariables(ID3D12Device *pd3dDevice, ID3D12GraphicsCommandList *pd3dCommandList)
{
	UINT ncbElementBytes = ((sizeof(CB_GAMEOBJECT_INFO) + 255) & ~255); //256�� ���
	m_pd3dcbTreeGameObjects = ::CreateBufferResource(pd3dDevice, pd3dCommandList, NULL, ncbElementBytes * m_nTreeObjects, D3D12_HEAP_TYPE_UPLOAD, D3D12_RESOURCE_STATE_VERTEX_AND_CONSTANT_BUFFER, NULL);

	m_pd3dcbTreeGameObjects->Map(0, NULL, (void **)&m_pcbMappedTreeGameObjects);
}

void CBillboardTreeArrayShader::UpdateShaderVariables(ID3D12GraphicsCommandList *pd3dCommandList)
{
	UINT ncbElementBytes = ((sizeof(CB_GAMEOBJECT_INFO) + 255) & ~255);
	for (int j = 0; j < m_nTreeObjects; j++)
	{
		CB_GAMEOBJECT_INFO *pbMappedcbTreeGameObject = (CB_GAMEOBJECT_INFO *)((UINT8 *)m_pcbMappedTreeGameObjects + (j * ncbElementBytes));
		XMStoreFloat4x4(&pbMappedcbTreeGameObject->m_xmf4x4World, XMMatrixTranspose(XMLoadFloat4x4(&m_ppTreeObjects[j]->m_xmf4x4World)));
	}
}

void CBillboardTreeArrayShader::ReleaseShaderVariables()
{
	if (m_pd3dcbTreeGameObjects)
	{
		m_pd3dcbTreeGameObjects->Unmap(0, NULL);
		m_pd3dcbTreeGameObjects->Release();
	}

	CTexturedShader::ReleaseShaderVariables();
}

D3D12_SHADER_BYTECODE CBillboardTreeArrayShader::CreateVertexShader(ID3DBlob **ppd3dShaderBlob)
{
	return(CShader::CompileShaderFromFile(L"Shaders.hlsl", "VSTreeArray", "vs_5_1", ppd3dShaderBlob));
}

D3D12_SHADER_BYTECODE CBillboardTreeArrayShader::CreatePixelShader(ID3DBlob **ppd3dShaderBlob)
{
	return(CShader::CompileShaderFromFile(L"Shaders.hlsl", "PSTreeArray", "ps_5_1", ppd3dShaderBlob));
}

void CBillboardTreeArrayShader::BuildObjects(ID3D12Device *pd3dDevice, ID3D12GraphicsCommandList *pd3dCommandList, void *pContext)
{
	CHeightMapTerrain *pTerrain = (CHeightMapTerrain *)pContext;
	//
	float fxPitch = 200.0f;
	float fzPitch = 200.0f;
	//
	float fTerrainWidth = pTerrain->GetWidth();
	float fTerrainLength = pTerrain->GetLength();
	//
	int xObjects = int(fTerrainWidth / fxPitch);	// x������ ��� �׸�����. ���� x�� ������ �� �.
	int zObjects = int(fTerrainLength / fzPitch);	// z������ ��� �׸�����.	���� z�� ������ �� �.

	m_nTreeObjects = (xObjects * zObjects);			// �� ��ü�� �׸� ������Ʈ ����.
	cout << m_nTreeObjects << endl;
	// �ؽ�ó ����
	CTexture* pTexture;

	pTexture = new CTexture(1, RESOURCE_TEXTURE2DARRAY, 0);
	pTexture->LoadTextureFromFile(pd3dDevice, pd3dCommandList, L"Image/treearray.dds", 0);
	

	UINT ncbElementBytes = ((sizeof(CB_GAMEOBJECT_INFO) + 255) & ~255);

	CreateCbvAndSrvDescriptorHeaps(pd3dDevice, pd3dCommandList, m_nTreeObjects, 1);	// srv 1��. �ؽ�ó 1�� ���ϱ�.
	CreateShaderVariables(pd3dDevice, pd3dCommandList);
	CreateConstantBufferViews(pd3dDevice, pd3dCommandList, m_nTreeObjects, m_pd3dcbTreeGameObjects, ncbElementBytes);
	CreateShaderResourceViews(pd3dDevice, pd3dCommandList, pTexture, 7, true);

	// ���� ���� �� �ؽ�ó ����
	CMaterial *m_pMaterial = new CMaterial();
	m_pMaterial->SetTexture(pTexture);

	// �޽� ����
	CTexturedRectMesh *pRectMesh = new CTexturedRectMesh(pd3dDevice, pd3dCommandList, 50.0f, 70.0f, 0.0f, 0, 0, 0);

	// ��ü �����Ҵ�
	m_ppTreeObjects = new CBillboardObject*[m_nTreeObjects];

	CBillboardObject *pBillboardObject = NULL;
	float xPosition;
	float zPosition;
	for (int i = 0, x = xObjects; x < xObjects*2; x++)
	{
		for (int z = 0; z < zObjects; z++)
		{
			if (i % 2) {
				xPosition = x * fxPitch / 2 + 4;
				zPosition = z * fzPitch + 4;
			}
			xPosition = x * fxPitch / 2;		// ������ ������ �� x������ fxPitch��ŭ �������ֵ���.
			zPosition = z * fzPitch;		// ������ ������ �� z������ fxPitch��ŭ �������ֵ���.

			pBillboardObject = new CBillboardObject(1);

			pBillboardObject->SetMesh(0, pRectMesh);
			pBillboardObject->SetMaterial(m_pMaterial);
			float fHeight = pTerrain->GetHeight(xPosition, zPosition);
			pBillboardObject->SetPosition(xPosition, fHeight + 30.0f, zPosition);
			pBillboardObject->SetCbvGPUDescriptorHandlePtr(m_d3dCbvGPUDescriptorStartHandle.ptr + (::gnCbvSrvDescriptorIncrementSize * i));
			m_ppTreeObjects[i++] = pBillboardObject;
		}
	}
}

void CBillboardTreeArrayShader::ReleaseObjects()
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

void CBillboardTreeArrayShader::AnimateObjects(float fTimeElapsed)
{
	//for (int j = 0; j < m_nTreeObjects; j++)
	//{
	//	m_ppTreeObjects[j]->Animate(fTimeElapsed, m_pCamera);
	//}
}

void CBillboardTreeArrayShader::ReleaseUploadBuffers()
{
	if (m_ppTreeObjects)
	{
		for (int j = 0; j < m_nTreeObjects; ++j) if (m_ppTreeObjects[j]) m_ppTreeObjects[j]->ReleaseUploadBuffers();
	}
}

void CBillboardTreeArrayShader::Render(ID3D12GraphicsCommandList *pd3dCommandList, CCamera *pCamera)
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

void CTerrainShader::CreateShader(ID3D12Device *pd3dDevice, ID3D12RootSignature *pd3dGraphicsRootSignature)
{
	CShader::CreateShader(pd3dDevice, pd3dGraphicsRootSignature);
}

