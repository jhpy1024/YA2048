#ifndef GAME_HPP
#define GAME_HPP

#include <SFML/Graphics.hpp>
#include <string>

#include "Grid.hpp"

class Game
{
public:
	Game();

	void run();

	void handleInput();
	void handleKeyPress(const sf::Event& event);

	void update(sf::Time delta);
	void render();

private:
	void updateScoreText();
	
private:
	static const float WIDTH;
	static const float HEIGHT;
	static const std::string TITLE;

	sf::RenderWindow m_Window;

	sf::Clock m_Clock;
	sf::Time m_LastFrameTime;

	Grid m_Grid;

	bool m_GameOver;
	sf::RectangleShape m_GameOverOverlay;
	sf::Font m_GameOverFont;
	sf::Text m_GameOverText;

	sf::Text m_ScoreText;
};

#endif