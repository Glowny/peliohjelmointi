#pragma once
#include <vector>
#include <typeinfo>
#include <unordered_map>
#include <assert.h>
#include "SFML\System.hpp"
#include "Component.h"
#include "RenderComponent.h"
#include "TransformComponent.h"
class GameObject
{
public:
	GameObject();
	~GameObject(); 
	void addComponent(Component* component);
	//RenderComponent renderComponent;
	//TransformComponent transformComponent;
	//std::vector<Component*> components; 
	Drawable GetFinalDrawable();

	template<typename T>
	T* getComponent();
	void update();
private:
	sf::Vector2f getLocation();
	sf::VertexArray move(sf::VertexArray draw, sf::Vector2f move);
	// addcomponent ja getcomponent loppuun
	using ComponentMap = std::unordered_map <const std::type_info*, Component* > ;
	ComponentMap _components;
};

template<typename T>
T* GameObject::getComponent()
{
	ComponentMap::const_iterator position = _components.find(&typeid(T));

	if (position == _components.end())
	{
		return nullptr;
	}
	else
	{
		return static_cast<T*>(position->second);
	}
}