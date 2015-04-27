#include "SFML\Graphics.hpp"
#include "SFML\Window.hpp"
#include "SFML\System.hpp"

#include "GameObject.h"
#include "TransformComponent.h"
#include "RenderComponent.h"
#include "RenderComponentFactory.h"
#include "RenderSystem.h"
#include "TransformSystem.h"
#include "SystemManager.h"
#include <vector>
int main()
{
	SystemManager systemManager;
	systemManager.AddSystem(new TransformSystem());
	RenderSystem* renderSystem = new RenderSystem();
	systemManager.AddSystem(renderSystem);

	renderSystem->CreateWindow(sf::Vector2i(900, 1100), "Deep lake simulator");
	RenderComponentFactory renderCFactory;

	std::vector<GameObject*> gameObjects;

	GameObject gameObject;
	gameObject.addComponent(new TransformComponent(sf::Vector2f(100, 200)));
	gameObject.addComponent(renderCFactory.create("fish.png", sf::Vector2f(300, 100)));
	gameObject.getComponent<TransformComponent>()->location = sf::Vector2f(0, 0);
	gameObject.getComponent<TransformComponent>()->speed = sf::Vector2f(0.01, 0.02);

	GameObject gameObject2;
	gameObject2.addComponent(new TransformComponent(sf::Vector2f(200, 200)));
	gameObject2.addComponent(renderCFactory.create("fish.png", sf::Vector2f(150, 200)));
	gameObject2.getComponent<TransformComponent>()->location = sf::Vector2f(400, 400);
	gameObject2.getComponent<TransformComponent>()->speed = sf::Vector2f(-0.01, -0.03);

	GameObject gameObject3;
	gameObject3.addComponent(new TransformComponent(sf::Vector2f(400, 400)));
	gameObject3.addComponent(renderCFactory.create(sf::Vector2f(100, 100)));
	gameObject3.getComponent<TransformComponent>()->location = sf::Vector2f(204, 630);
	gameObject3.getComponent<TransformComponent>()->speed = sf::Vector2f(-0.1, 0.01);

	gameObjects.push_back(&gameObject);
	gameObjects.push_back(&gameObject2);
	gameObjects.push_back(&gameObject3);

	systemManager.SetGameObjectVector(gameObjects);
	
	bool windowIsOpen = true;
	while (windowIsOpen)
	{
		windowIsOpen = renderSystem->PollEvent();

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
			gameObject.removeComponent<RenderComponent>();
		
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
			gameObject.addComponent(renderCFactory.create("fish.png", sf::Vector2f(300,100)));

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
			gameObject.removeComponent<TransformComponent>();

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::F))
			gameObject.addComponent(new TransformComponent(sf::Vector2f(300, 300)));

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::G))
			if (gameObject.getComponent<TransformComponent>() != nullptr)
			gameObject.getComponent<TransformComponent>()->speed += sf::Vector2f(0.01f, 0.0f);
		systemManager.Update();

		if (gameObject.getComponent<TransformComponent>() != nullptr)
		{
			if (gameObject.getComponent<TransformComponent>()->location.x > 1200)
				gameObject.getComponent<TransformComponent>()->location.x = -300;
		}
		for (unsigned int i = 0; i < gameObjects.size(); i++)
		{
			gameObjects[i]->Update();
		}

		renderSystem->Draw();
	}
}

