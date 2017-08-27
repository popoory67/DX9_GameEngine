#pragma once


template<class T>
class Matrix
{
public:
	using Type = T;

public:

	Matrix()
	{

	}

	virtual ~Matrix()
	{

	}

	virtual T Transform() = 0;

	virtual T SetScale( float xpos = 1, float ypos = 1, float zpos = 1 ) = 0;
	virtual T SetRotate( float xpos = 0, float ypos = 0, float zpos = 0 ) = 0;
	virtual T SetPosition( float xpos = 0, float ypos = 0, float zpos = 0 ) = 0;
};

