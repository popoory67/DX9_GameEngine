// -------------------------------------------------------------
// HLSL
// -------------------------------------------------------------

// -------------------------------------------------------------
// ��������
// -------------------------------------------------------------
float4x4 mWVP;        // ����->�������� ��ǥ��ȯ
float4x4 mWIT;
float4x4  mVP : VIEWPROJECTION;
float4 Color;


struct VS_OUTPUT
{
    float4 Pos        : POSITION;
    float4 Color      : COLOR0;
};

VS_OUTPUT VS (
		float4 Pos      : POSITION,          // ������ġ��ǥ
		float4 Diffuse  : COLOR0
)
{
    VS_OUTPUT Out = (VS_OUTPUT)0;        // ��µ�����
    
    Out.Pos = mul( Pos, mWVP );            // ��ġ��ȯ
    Out.Color =  Diffuse; 
    return Out;
}


float4 PS ( VS_OUTPUT In ) : COLOR
{
    return Color ;
}


// -------------------------------------------------------------
// ��ũ��
// -------------------------------------------------------------
technique TShader          
{
    pass P0
    {
        // ���̴�
        VertexShader = compile vs_1_1 VS();
        PixelShader  = compile ps_2_0 PS();
    }
}
