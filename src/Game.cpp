#include "Game.hpp"

#include <iostream>

const float Game::WIDTH = 400;
const float Game::HEIGHT = 600;
const std::string Game::TITLE = "Yet Another 2048 Clone!";

Game::Game()
	: m_Window(sf::VideoMode(WIDTH, HEIGHT), TITLE, sf::Style::Close)
	, m_Grid({ WIDTH / 2.f - WIDTH * (2.f / 2.3f) / 2.f, HEIGHT / 2.f - WIDTH * (2.f / 2.3f) / 2.f },
			 { WIDTH * (2.f / 2.3f), WIDTH * (2.f / 2.3f) })
	, m_GameOver(false)
{
	m_GameOverOverlay.setSize({ WIDTH, HEIGHT });
	m_GameOverOverlay.setFillColor(sf::Color(128, 0, 0, 128));

	m_GameOverFont.loadFromFile("res/fonts/Ubuntu-M.ttf");
	m_GameOverText.setFont(m_GameOverFont);
	m_GameOverText.setCharacterSize(24);
	m_GameOverText.setString("          Game Over!\nPress [SPACE] to retry\nOr [ESCAPE] to go back");
	auto localBounds = m_GameOverText.getLocalBounds();
	m_GameOverText.setOrigin(localBounds.left + localBounds.width / 2.f, localBounds.top + localBounds.height / 2.f);
	m_GameOverText.setPosition(WIDTH / 2.f, HEIGHT / 2.f);

	m_ScoreText.setFont(m_GameOverFont);
	m_ScoreText.setCharacterSize(48);
	m_ScoreText.setColor(sf::Color::Black);
	m_ScoreText.setString("Score: 0");
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
	if (m_GameOver)
	{
		if (event.key.code == sf::Keyboard::Space)
			m_Grid.reset("tryAgain");
		else if (event.key.code == sf::Keyboard::Escape)
			m_Grid.reset("goBack");
	}
	if (!m_GameOver)
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
}

void Game::update(sf::Time delta)
{
	m_GameOver = m_Grid.isGameOver();

	updateScoreText();
}

void Game::render()
{
	auto absCosOfTime = std::abs(std::cos(m_Clock.getElapsedTime().asSeconds() / 3));
	auto red = 50 + absCosOfTime * 205;
	auto green = 50 + absCosOfTime * 205;
	auto blue = 50 + absCosOfTime * 205;

	m_Window.clear(sf::Color(red, green, blue));

	m_Window.draw(m_Grid);
	m_Window.draw(m_ScoreText);

	if (m_GameOver)
	{
		m_Window.draw(m_GameOverOverlay);
		m_Window.draw(m_GameOverText);
	}

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

void Game::updateScoreText()
{
	m_ScoreText.setString("Score: " + std::to_string(m_Grid.getScore()));
	auto bounds = m_ScoreText.getLocalBounds();
	m_ScoreText.setOrigin(bounds.left + bounds.width / 2.f, bounds.top + bounds.height / 2.f);
	m_ScoreText.setPosition(WIDTH / 2.f, HEIGHT * 0.1f);
}