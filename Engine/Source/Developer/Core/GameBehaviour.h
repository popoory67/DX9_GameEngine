#pragma once

#include "Component.h"

// GameObject�� GameBehaviour�� �߰��ϰ� �����Ŵ
// custom component
class GameBehaviour : public Component
{
public:
	GameBehaviour();
	virtual ~GameBehaviour();

	// message �Լ��� : unity�� Monobehaviour �����ϱ�
	virtual void Start();

	virtual void Update();

	virtual void Release();
};

