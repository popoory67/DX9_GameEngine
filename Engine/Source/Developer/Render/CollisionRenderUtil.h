#pragma once

#include <d3dx9.h>
#include <btBulletDynamicsCommon.h>

namespace CollisionRender
{
	static D3DXMATRIX btTransformToD3DXMATIRX( const btTransform& transform )
	{
		btVector3 R = transform.getBasis().getColumn( 0 );
		btVector3 U = transform.getBasis().getColumn( 1 );
		btVector3 L = transform.getBasis().getColumn( 2 );
		btVector3 P = transform.getOrigin();

		D3DXMATRIX mat;
		mat._11 = R.m_floats[0]; mat._12 = R.m_floats[1]; mat._13 = R.m_floats[2]; mat._14 = 0.f;
		mat._21 = U.m_floats[0]; mat._22 = U.m_floats[1]; mat._23 = U.m_floats[2]; mat._24 = 0.f;
		mat._31 = L.m_floats[0]; mat._32 = L.m_floats[1]; mat._33 = L.m_floats[2]; mat._34 = 0.f;
		mat._41 = P.m_floats[0]; mat._42 = P.m_floats[1]; mat._43 = P.m_floats[2]; mat._44 = 1.f;

		return mat;
	}
}