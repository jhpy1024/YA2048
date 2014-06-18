#include "Game.hpp"

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
			default:
				break;
		}
	}
}

void Game::update(sf::Time delta)
{

}

void Game::render()
{
	m_Window.clear(sf::Color(133, 214, 255, 255));

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