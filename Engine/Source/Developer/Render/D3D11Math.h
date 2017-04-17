#pragma once

#include <DirectXMath.h>

using namespace DirectX;


namespace D3D11Math
{
	// x, y, z vector
	struct Vector3 : public XMFLOAT3
	{
		Vector3();
		Vector3( const Vector3& vec );
		Vector3( float x, float y, float z );

		Vector3& operator = (const Vector3& vector3);

		Vector3 operator + (const Vector3& vector3) const;
		Vector3 operator - (const Vector3& vector3) const;
		Vector3 operator * (float mul) const;
		Vector3 operator / (float mul) const;

		bool operator == (const Vector3& vector3) const;
		bool operator != (const Vector3& vector3) const;
	};

	struct Vector2
	{
		float x, y;
	};

	// the cross product
	Vector3* Vec3Cross( Vector3* out, const Vector3* vec1, const Vector3* vec2 );

	// the normalized product
	Vector3* Vec3Normalize( Vector3* out, const Vector3* vec );
}