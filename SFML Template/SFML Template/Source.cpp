#include <SFML\Graphics.hpp>
#include <iostream>
#include "Animation.h"
#include "Player.h"
#include "Platform.h"

static const float VIEW_HEIGHT = 512.0f;

void ResizeView(const sf::RenderWindow& window, sf::View& view)
{
	float aspectRatio = static_cast<float>(window.getSize().x) / static_cast<float>(window.getSize().y);
	view.setSize(VIEW_HEIGHT * aspectRatio, VIEW_HEIGHT);
}

int main()
{

	sf::RenderWindow window(sf::VideoMode(512, 512), "SFML Tutorial", sf::Style::Close | sf::Style::Resize);
	sf::View view(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(512.0f, 512.0f));
	sf::Texture playerTexture;
	playerTexture.loadFromFile("tux_from_linux.png");

	Player player(&playerTexture, sf::Vector2u(3, 9), 0.2f, 100.0f);

	Platform platForm1(nullptr, sf::Vector2f(400.0f, 200.0f), sf::Vector2f(500.0f, 200.0f));
	Platform platForm2(nullptr, sf::Vector2f(400.0f, 200.0f), sf::Vector2f(500.0f, 0.0f));

	float deltaTime = 0.0f;
	sf::Clock clock;

	while (window.isOpen())
	{
		deltaTime = clock.restart().asSeconds();

		sf::Event evnt;
		while (window.pollEvent(evnt))
		{
			switch (evnt.type)
			{
			case sf::Event::Closed:
				window.close();
				break;

			case sf::Event::Resized:
				ResizeView(window, view);
				break;

			default:
				break;
			}
		}

		player.Update(deltaTime);

		platForm1.GetCollider().CheckCollision(player.GetCollider(), 0.0f);
		platForm2.GetCollider().CheckCollision(player.GetCollider(), 1.0f);

		view.setCenter(player.GetPosition());


		window.clear(sf::Color(150, 150, 150));
		window.setView(view);
		player.Draw(window);
		platForm1.Draw(window);
		platForm2.Draw(window);
		window.display();
	}

	system("pause");
	return 0;
}