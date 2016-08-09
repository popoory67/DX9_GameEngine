#pragma once

#include "CorePCH.h"

class GameObject
{
public:
	GameObject();
	virtual ~GameObject();

	virtual void Start();

	virtual void Update();

	virtual void Release();

	// equal
	// Getcomponent, Addcomponent �پ��� ���·�
	// 

	/**
	 * GameObject�� ��ӹ��� Ŭ������ �޾ƿ� ������Ʈ�� �߰���
	 */
	void AddComponent(GameObject* component);

	/**
	 * �߰��� ������Ʈ�� ã�� ������
	 * @return the type of component
	 */
	template<class Type>
	Type GetComponent()
	{
		for (auto iter = _componentVector.begin(); iter != _componentVector.end(); iter++)
		{
			auto component = dynamic_cast<Type*>(*iter);

			if (!component)
			{
				delete (component);
				component = nullptr;

				continue;
			}

			return *component;
		}
	
		//return nullptr;
	}

private:

	vector<GameObject*> _componentVector;

};

