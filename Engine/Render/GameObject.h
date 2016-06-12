#pragma once

#include "RenderPCH.h"

class GameObject
{
public:
	GameObject();
	virtual ~GameObject();

	virtual void Start();

	virtual void Update();

	virtual void Release();

protected:

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
				SAFE_DELETE(component);

				continue;
			}

			return *component;
		}
	
		//return nullptr;
	}

private:

	vector<GameObject*> _componentVector;

};

