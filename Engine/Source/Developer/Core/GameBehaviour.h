#pragma once

#include "Component.h"

// GameObject에 GameBehaviour를 추가하고 실행시킴
// custom component
class GameBehaviour : public Component
{
public:
	GameBehaviour();
	virtual ~GameBehaviour();

	// message 함수들 : unity의 Monobehaviour 참고하기
	virtual void Start();

	virtual void Update();

	virtual void Release();
};

