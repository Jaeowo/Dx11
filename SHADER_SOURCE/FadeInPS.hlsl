#include "globals.hlsli"
struct VSIn
{
    float4 Pos : POSITION;
    float4 Color : COLOR;
    float2 UV : TEXCOORD;
};

struct VSOut
{
    float4 Pos : SV_Position;
    float4 Color : COLOR;
    float2 UV : TEXCOORD;
};

float4 main(VSOut In) : SV_Target
{
    float4 Color = float4(0.0f, 0.0f, 0.0f, 1.0f);
   
    Color.a -= FadeAmount;

    if (Color.a <= 0.0f)
    {
        Color.a = 0.0f;
    }
   

    return Color;
}
