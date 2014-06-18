#ifndef GRID_HPP
#define GRID_HPP

#include <SFML/Graphics.hpp>
#include <vector>

class Grid : public sf::Drawable, public sf::Transformable
{
public:
	Grid(const sf::Vector2f& position, const sf::Vector2f& size);

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	sf::Vector2f getSize() const;

private:
	const int NUM_CELLS;
	const float CELL_WIDTH;
	const float CELL_HEIGHT;

	sf::Vector2f m_Size;

	sf::RectangleShape m_Background;
	std::vector<sf::RectangleShape> m_Lines;
};

#endif