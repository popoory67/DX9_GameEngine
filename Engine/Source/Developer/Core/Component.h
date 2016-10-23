#pragma once

#include "CorePCH.h"

class Component
{
public:
	Component();
	virtual ~Component();

	// equal
	// Getcomponent, Addcomponent �پ��� ���·�

	// GameObject�� ��ӹ��� Ŭ������ �޾ƿ� ������Ʈ�� �߰���
	void AddComponent( Component* component );

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

