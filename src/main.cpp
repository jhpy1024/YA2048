#include <iostream>
#include <SFML/Graphics.hpp>

int main()
{
	sf::RenderWindow window(sf::VideoMode(640, 640), "Test");

	sf::RectangleShape leftVertical({ 1.f, 640.f });
	sf::RectangleShape rightVertical({ 1.f, 640.f });
	sf::RectangleShape topHorizontal({ 640.f, 1.f });
	sf::RectangleShape bottomHorizontal({ 640.f, 1.f });

	leftVertical.setPosition({ window.getSize().x / 3.f, 0.f });
	rightVertical.setPosition({ window.getSize().x / 3.f * 2.f, 0.f });
	topHorizontal.setPosition({ 0.f, window.getSize().y / 3.f });
	bottomHorizontal.setPosition({ 0.f, window.getSize().y / 3.f * 2.f });

	leftVertical.setFillColor(sf::Color::Red);
	rightVertical.setFillColor(sf::Color::Green);
	topHorizontal.setFillColor(sf::Color::Yellow);
	bottomHorizontal.setFillColor(sf::Color::Blue);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();
		window.draw(leftVertical);
		window.draw(rightVertical);
		window.draw(topHorizontal);
		window.draw(bottomHorizontal);
		window.display();
	}

	return 0;
}























