#pragma once

#include "CorePCH.h"

class Component
{
public:
	Component();
	virtual ~Component();

	// equal
	// Getcomponent, Addcomponent 다양한 형태로

	// GameObject를 상속받은 클래스를 받아와 컴포넌트로 추가함
	void AddComponent( Component* component );

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
				// component = nullptr;

				continue;
			}

			return *component;
		}
	}

protected:

	string _name;

private:

	vector<Component*> _componentVector;

};

