#include "Grid.hpp"

Grid::Grid(const sf::Vector2f& size)
	: NUM_CELLS(4)
	, m_Size(size)
	, m_Background(size)
{
	m_Background.setFillColor(sf::Color(37, 179, 250, 255));

	sf::RectangleShape line;

	for (int i = 0; i < NUM_CELLS + 1; ++i)
	{
		line.setFillColor(sf::Color(133, 214, 255, 255));
		line.setPosition(getPosition().x + (m_Size.x / NUM_CELLS) * i, getPosition().y);
		line.setSize({ 1.f, m_Size.y });
		m_Lines.push_back(line);

		line.setPosition(getPosition().x, getPosition().y + (m_Size.y / NUM_CELLS) * i);
		line.setSize({ m_Size.x, 1.f });
		m_Lines.push_back(line);
	}
}

void Grid::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();

	target.draw(m_Background, states);

	for (auto& line : m_Lines)
		target.draw(line, states);
}

sf::Vector2f Grid::getSize() const
{
	return m_Size;
}