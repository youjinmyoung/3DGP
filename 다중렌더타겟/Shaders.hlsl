cbuffer cbPlayerInfo : register(b0)
{
	matrix		gmtxPlayerWorld : packoffset(c0);
};

cbuffer cbCameraInfo : register(b1)
{
	matrix		gmtxView : packoffset(c0);
	matrix		gmtxProjection : packoffset(c4);
	float3		gvCameraPosition : packoffset(c8);
};

cbuffer cbGameObjectInfo : register(b2)
{
	matrix		gmtxGameObject : packoffset(c0);
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
struct VS_DIFFUSED_INPUT
{
	float3 position : POSITION;
	float4 color : COLOR;
};

struct VS_DIFFUSED_OUTPUT
{
	float4 position : SV_POSITION;
	float4 color : COLOR;
};

VS_DIFFUSED_OUTPUT VSPlayer(VS_DIFFUSED_INPUT input)
{
	VS_DIFFUSED_OUTPUT output;

	output.position = mul(mul(mul(float4(input.position, 1.0f), gmtxPlayerWorld), gmtxView), gmtxProjection);
	output.color = input.color;

	return(output);
}

float4 PSPlayer(VS_DIFFUSED_OUTPUT input) : SV_TARGET
{
	return(input.color);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
Texture2D gtxtTexture : register(t0);
SamplerState gSamplerState : register(s0);

struct VS_TEXTURED_INPUT
{
	float3 position : POSITION;
	float2 uv : TEXCOORD;
};

struct VS_TEXTURED_OUTPUT
{
	float4 position : SV_POSITION;
	float2 uv : TEXCOORD;
};

VS_TEXTURED_OUTPUT VSTextured(VS_TEXTURED_INPUT input)
{
	VS_TEXTURED_OUTPUT output;

	output.position = mul(mul(mul(float4(input.position, 1.0f), gmtxGameObject), gmtxView), gmtxProjection);
	output.uv = input.uv;

	return(output);
}

float4 PSTextured(VS_TEXTURED_OUTPUT input) : SV_TARGET
{
	float4 cColor = gtxtTexture.Sample(gSamplerState, input.uv);

	return(cColor);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
Texture2D gtxtTerrainBaseTexture : register(t1);
Texture2D gtxtTerrainDetailStoneTexture : register(t2);

struct VS_TERRAIN_INPUT
{
	float3 position : POSITION;
	float4 color : COLOR;
	float2 uv0 : TEXCOORD0;
	float2 uv1 : TEXCOORD1;
};

struct VS_TERRAIN_OUTPUT
{
	float4 position : SV_POSITION;
	float4 color : COLOR;
	float2 uv0 : TEXCOORD0;
	float2 uv1 : TEXCOORD1;
};

VS_TERRAIN_OUTPUT VSTerrain(VS_TERRAIN_INPUT input)
{
	VS_TERRAIN_OUTPUT output;

	output.position = mul(mul(mul(float4(input.position, 1.0f), gmtxGameObject), gmtxView), gmtxProjection);
	output.color = input.color;
	output.uv0 = input.uv0;
	output.uv1 = input.uv1;

	return(output);
}

float4 PSTerrain(VS_TERRAIN_OUTPUT input) : SV_TARGET
{
	float4 cBaseTexColor = gtxtTerrainBaseTexture.Sample(gSamplerState, input.uv0);
	float4 cDetailStoneTexColor = gtxtTerrainDetailStoneTexture.Sample(gSamplerState, input.uv1);
	float4 cColor = input.color * saturate((cBaseTexColor * 0.5f) + (cDetailStoneTexColor * 0.5f));

	return(cColor);
}

Texture2D gtxtTreeTexture[5] : register(t3);

VS_TEXTURED_OUTPUT VSTree(VS_TEXTURED_INPUT input)
{
	VS_TEXTURED_OUTPUT output;

	output.position = mul(mul(mul(float4(input.position, 1.0f), gmtxGameObject), gmtxView), gmtxProjection);
	output.uv = input.uv;

	return(output);
}

float4 PSTree(VS_TEXTURED_OUTPUT input) : SV_TARGET
{
	
	float4 cColor = gtxtTreeTexture[0].Sample(gSamplerState, input.uv);

	return(cColor);
}

Texture2DArray gtxtTreeTextureArray : register(t8);

struct VS_IN
{
	float3 posW			: POSITION;
	float2 sizeW		: SIZE;
};

struct VS_OUT
{
	float3 centerW		: POSITION;
	float2 sizeW		: SIZE;
};

struct GS_OUT
{
	float4 posH			: SV_POSITION;
	float3 posW			: POSITION;
	float3 normalW		: NORMAL;
	float2 uv			: TEXCOORD;
	uint primID			: SV_PrimitiveID;
};

VS_OUT VS_Geometry(VS_IN input)
{
	VS_OUT output;
	output.centerW = input.posW;
	output.sizeW = input.sizeW;
	return output;
}

[maxvertexcount(4)]
void GS(point VS_OUT input[1], uint primID : SV_PrimitiveID, inout TriangleStream<GS_OUT> outStream)
{
	float3 vUp = float3(0.0f, 1.0f, 0.0f);
	float3 vLook = gvCameraPosition.xyz - input[0].centerW;
	vLook = normalize(vLook);
	float3 vRight = cross(vUp, vLook);

	float fHalfW = input[0].sizeW.x * 0.5f;
	float fHalfH = input[0].sizeW.y * 0.5f;

	// 사각형 정점들을 월드변환행렬로 변환하고, 그것들을 하나의 삼각형으로 출력
	float4 pVertices[4];
	pVertices[0] = float4(input[0].centerW + fHalfW * vRight - fHalfH * vUp, 1.0f);
	pVertices[1] = float4(input[0].centerW + fHalfW * vRight + fHalfH * vUp, 1.0f);
	pVertices[2] = float4(input[0].centerW - fHalfW * vRight - fHalfH * vUp, 1.0f);
	pVertices[3] = float4(input[0].centerW - fHalfW * vRight + fHalfH * vUp, 1.0f);

	float2 pUVs[4] = { float2(0.0f, 1.0f), float2(0.0f, 0.0f), float2(1.0f, 1.0f), float2(1.0f, 0.0f) };

	GS_OUT output;
	[unroll]
	for (int i = 0; i < 4; ++i)
	{
		output.posW = pVertices[i].xyz;
		output.posH = mul(mul(pVertices[i], gmtxView), gmtxProjection);
		output.normalW = vLook;
		output.uv = pUVs[i];
		output.primID = primID;
		outStream.Append(output);
	}
}

float4 PS_Geometry(GS_OUT input) : SV_Target
{
	float3 uvw = float3(input.uv, input.primID % 3);	// 텍스처의 인덱스 설정
	
	float4 cColor = gtxtTreeTextureArray.Sample(gSamplerState, uvw);

	return (cColor);
}

//VS_TEXTURED_OUTPUT VSTreeArray(VS_TEXTURED_INPUT input)
//{
//	VS_TEXTURED_OUTPUT output;
//
//	output.position = mul(mul(mul(float4(input.position, 1.0f), gmtxGameObject), gmtxView), gmtxProjection);
//	output.uv = input.uv;
//
//	return(output);
//}
//
//float4 PSTreeArray(VS_TEXTURED_OUTPUT input) : SV_TARGET
//{
//	float3 uvw = float3(input.uv, 1);
//	float4 cColor = gtxtTreeTextureArray.Sample(gSamplerState, uvw);
//
//	return(cColor);
//}

struct VS_POSTPROCESSING_OUTPUT
{
	float4 position : SV_POSITION;
	float2 uv : TEXCOORD;
	uint vertex_id : VERTEXID;
};

VS_POSTPROCESSING_OUTPUT VSPostProcessing(uint nVertexID : SV_VertexID)
{
	VS_POSTPROCESSING_OUTPUT output;

	if (nVertexID == 0) {
		output.position = float4(-1.0f, -0.5f, 0.0f, 1.0f);
		output.uv = float2(0.f, 0.f);
	}
	if (nVertexID == 1) {
		output.position = float4(-0.5f, -0.5f, 0.0f, 1.0f);
		output.uv = float2(1.f, 0.f);
	}
	if (nVertexID == 2) {
		output.position = (float4(-0.5f, -1.0f, 0.0f, 1.0f));
		output.uv = float2(1.f, 1.f);
	}
	if (nVertexID == 3) {
		output.position = (float4(-1.0f, -0.5f, 0.0f, 1.0f));
		output.uv = float2(0.f, 0.f);
	}
	if (nVertexID == 4) {
		output.position = (float4(-0.5f, -1.0f, 0.0f, 1.0f));
		output.uv = float2(1.f, 1.f);
	}
	if (nVertexID == 5) {
		output.position = (float4(-1.0f, -1.0f, 0.0f, 1.0f));
		output.uv = float2(0.f, 1.f);
	}
	output.vertex_id = nVertexID;

	return(output);
}

Texture2D<float4> gtxScene : register(t9);

float4 PSPostProcessing(VS_POSTPROCESSING_OUTPUT input) : SV_Target
{
	float4 cColor = gtxScene.SampleLevel(gSamplerState, input.uv, 0);

	return cColor;
}