// -------------------------------------------------------------
// HLSL
// -------------------------------------------------------------

// -------------------------------------------------------------
// 전역변수
// -------------------------------------------------------------
float4x4 mWVP;        // 로컬->투영공간 좌표변환
float4x4 mWIT;
float4x4  mVP : VIEWPROJECTION;
float4 Color;


struct VS_OUTPUT
{
    float4 Pos        : POSITION;
    float4 Color      : COLOR0;
};

VS_OUTPUT VS (
		float4 Pos      : POSITION,          // 로컬위치좌표
		float4 Diffuse  : COLOR0
)
{
    VS_OUTPUT Out = (VS_OUTPUT)0;        // 출력데이터
    
    Out.Pos = mul( Pos, mWVP );            // 위치변환
    Out.Color =  Diffuse; 
    return Out;
}


float4 PS ( VS_OUTPUT In ) : COLOR
{
    return Color ;
}


// -------------------------------------------------------------
// 테크닉
// -------------------------------------------------------------
technique TShader          
{
    pass P0
    {
        // 셰이더
        VertexShader = compile vs_1_1 VS();
        PixelShader  = compile ps_2_0 PS();
    }
}
