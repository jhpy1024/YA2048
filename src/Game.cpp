#include "Game.hpp"

#include <iostream>

const float Game::WIDTH = 400;
const float Game::HEIGHT = 600;
const std::string Game::TITLE = "Yet Another 2048 Clone!";

Game::Game()
	: m_Window(sf::VideoMode(WIDTH, HEIGHT), TITLE)
	, m_Grid({ WIDTH / 2.f - WIDTH * (2.f / 2.3f) / 2.f, HEIGHT / 2.f - WIDTH * (2.f / 2.3f) / 2.f },
			 { WIDTH * (2.f / 2.3f), WIDTH * (2.f / 2.3f) })
{
	
}

void Game::handleInput()
{
	sf::Event event;
	while (m_Window.pollEvent(event))
	{
		switch (event.type)
		{
			case sf::Event::Closed:
				m_Window.close();
			break;
			case sf::Event::KeyPressed:
				handleKeyPress(event);
			break;
			default:
				break;
		}
	}
}

void Game::handleKeyPress(const sf::Event& event)
{
	if (event.key.code == sf::Keyboard::Up)
		m_Grid.moveUp();
	else if (event.key.code == sf::Keyboard::Down)
		m_Grid.moveDown();
	else if (event.key.code == sf::Keyboard::Left)
		m_Grid.moveLeft();
	else if (event.key.code == sf::Keyboard::Right)
		m_Grid.moveRight();
}

void Game::update(sf::Time delta)
{

}

void Game::render()
{
	auto absCosOfTime = std::abs(std::cos(m_Clock.getElapsedTime().asSeconds() / 3));
	auto red = 50 + absCosOfTime * 205;
	auto green = 50 + absCosOfTime * 205;
	auto blue = 50 + absCosOfTime * 205;

	m_Window.clear(sf::Color(red, green, blue));

	m_Window.draw(m_Grid);

	m_Window.display();
}

void Game::run()
{
	while (m_Window.isOpen())
	{
		auto currentTime = m_Clock.getElapsedTime();
		auto delta = currentTime - m_LastFrameTime;

		handleInput();
		update(delta);
		render();

		m_LastFrameTime = currentTime;
	}
}