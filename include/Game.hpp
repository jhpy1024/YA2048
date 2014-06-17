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
	void update(sf::Time delta);
	void render();
	
private:
	static const float WIDTH;
	static const float HEIGHT;
	static const std::string TITLE;

	sf::RenderWindow m_Window;

	sf::Clock m_Clock;
	sf::Time m_LastFrameTime;

	Grid m_Grid;
};

#endif