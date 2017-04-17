#include "RenderPCH.h"
#include "D3D11Math.h"
#include "Util.h"

namespace D3D11Math
{
	Vector3::Vector3()
	{

	}

	Vector3::Vector3( const Vector3& vec )
	{
		x = vec.x; 
		y = vec.y;
		z = vec.z;
	}

	Vector3::Vector3( float x, float y, float z )
	{ 
		XMFLOAT3( x, y, z ); 
	}

	Vector3& Vector3::operator = (const Vector3& vector3)
	{
		x = vector3.x;
		y = vector3.y;
		z = vector3.z;

		return *this;
	}

	Vector3 Vector3::operator + (const Vector3& vector3) const
	{
		return Vector3( x + vector3.x, y + vector3.y, z + vector3.z );
	}

	Vector3 Vector3::operator - (const Vector3& vector3) const
	{
		return Vector3( x - vector3.x, y - vector3.y, z - vector3.z );
	}

	Vector3 Vector3::operator * (float mul) const
	{
		return Vector3( x * mul, y * mul, z * mul );
	}

	Vector3 Vector3::operator / (float mul) const
	{
		if (mul == 0)
		{
			assert(Util::ErrorMessage("The parameter is 0. It is invaild access."));
		}

		return Vector3( x / mul, y / mul, z / mul );
	}

	bool Vector3::operator == (const Vector3& vector3) const
	{
		if (x == vector3.x && y == vector3.y && z == vector3.z)
		{
			return true;
		}

		return false;
	}

	bool Vector3::operator != (const Vector3& vector3) const
	{
		if (*this == vector3)
		{
			return false;
		}

		return true;
	}

	// the cross product
	Vector3* Vec3Cross( Vector3* out, const Vector3* vec1, const Vector3* vec2 )
	{
		if (!out || !vec1 || !vec2)
		{
			return nullptr;
		}

		Vector3 v;

		v.x = vec1->y * vec2->z - vec1->z * vec2->y;
		v.y = vec1->z * vec2->x - vec1->x * vec2->z;
		v.z = vec1->x * vec2->y - vec1->y * vec2->x;

		*out = v;

		return out;
	}

	// the normalized product
	Vector3* Vec3Normalize( Vector3* out, const Vector3* vec )
	{
		if (!out || !vec)
		{
			return nullptr;
		}

		float length = sqrt( (vec->x *vec->x) + (vec->y * vec->y) + (vec->z * vec->z) );

		out->x = vec->x / length;
		out->y = vec->y / length;
		out->z = vec->z / length;

		return out;
	}
}