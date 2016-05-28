float4x4 mWorld	: World;
float4x4 mWVP	: WorldViewProjection;
float4x4 mWIT	: WorldInverseTranspose;
float3 vEye;

float3 lightPos = { 1.f, 10.f, -100.f };
float4 lightColor = { 1.f, 1.f, 1.f, 1.f };
float4 sceneAmbient = { 0.5f, 0.5f, 0.5f, 1.f };



// Diffuse options.
float4 diffuseColor = { 0.65f, 0.65f, 0.7f, 1.f };
texture texDiffuse;
sampler tsDiffuse = sampler_state { Texture = (texDiffuse); MipFilter = LINEAR; MinFilter = LINEAR; MagFilter = LINEAR; };
bool useDiffuseTexture = false;


// Specular options.
float4 specularColor = { 1.f, 1.f, 1.f, 1.f };
texture texSpecular;
sampler tsSpecular = sampler_state { Texture = (texSpecular); MipFilter = LINEAR; MinFilter = LINEAR; MagFilter = LINEAR; };
float specularPower = 128.f;
bool useSpecularTexture = false;


// Ambient options.
float4 ambientColor = {0.1f, 0.1f, 0.1f, 1.f };
texture texAmbient;
sampler tsAmbient = sampler_state { Texture = (texAmbient); MipFilter = LINEAR; MinFilter = LINEAR; MagFilter = LINEAR; };
bool useAmbientTexture = false;





struct TInputVertex
{
	float4 pos			: POSITION;		// Position of this vertex
	float4 normal		: NORMAL;		// Position of the other vertex at the other end of the line.
	float2 tex0			: TEXCOORD0;	// Tex coords
};


struct TOutputVertex
{
	float4 hPos			: POSITION;
	float2 tex0			: TEXCOORD0;
	float3 L			: TEXCOORD1;
	float3 N			: TEXCOORD2;
	float3 V			: TEXCOORD3;
};




TOutputVertex mainVS( TInputVertex IN )
{
	TOutputVertex OUT = (TOutputVertex)0;
	
	float3 worldPos = mul( IN.pos, mWorld ).xyz;
	
	float3 V = normalize(vEye - worldPos);
	OUT.L = V;
	OUT.V = V;
	OUT.N = mul( IN.normal, mWIT );
	OUT.tex0 = IN.tex0;
	OUT.hPos = mul( IN.pos, mWVP );
	
	return OUT;
}



float4 mainPS( TOutputVertex IN, uniform bool bUseDiffuseTexture ) : COLOR
{
	float3 Ln = normalize( IN.L );
	float3 Nn = normalize( IN.N );
	float3 Vn = normalize( IN.V );
	float3 Hn = normalize( Vn + Ln );
	
	float4 finalColor = diffuseColor * dot(Nn,Ln) + ambientColor + sceneAmbient;
	
	if( bUseDiffuseTexture )
		finalColor *= tex2D( tsDiffuse, IN.tex0 );
		
	finalColor += specularColor * pow( dot(Nn,Hn), specularPower );
	return finalColor;
}


technique Textured
{
	pass p0
	{
		//cullmode = none;
		VertexShader = compile vs_2_0 mainVS();
		PixelShader = compile ps_2_0 mainPS( useDiffuseTexture );
	}
}