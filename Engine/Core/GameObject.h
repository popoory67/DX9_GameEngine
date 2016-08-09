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
	// Getcomponent, Addcomponent 다양한 형태로
	// 

	/**
	 * GameObject를 상속받은 클래스를 받아와 컴포넌트로 추가함
	 */
	void AddComponent(GameObject* component);

	/**
	 * 추가된 컴포넌트를 찾아 리턴함
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

