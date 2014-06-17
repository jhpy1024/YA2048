#include "Cell.hpp"

sf::Font Cell::m_Font;

Cell::Cell(const sf::Vector2f& position, const sf::Vector2f& size)
	: m_Shape(size)
	, m_Value(0)
	, m_IsEmpty(true)
{
	m_Font.loadFromFile("res/fonts/Ubuntu-M.ttf");

	m_Text.setFont(m_Font);
	m_Text.setCharacterSize(size.x);
	m_Text.setPosition(position);

	setPosition(position);
}

void Cell::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	if (m_IsEmpty)
		return;

	states.transform *= getTransform();

	target.draw(m_Shape, states);
	target.draw(m_Text, states);
}

void Cell::combine(Cell& cell)
{
	cell.setEmpty();
	setValue(m_Value + cell.getValue());
}

void Cell::setEmpty()
{
	m_IsEmpty = true;
}

void Cell::setValue(int value)
{
	m_Value = value;
	m_IsEmpty = false;
	m_Text.setString(std::to_string(m_Value));
}

int Cell::getValue() const
{
	return m_Value;
}

bool Cell::isEmpty() const
{
	return m_IsEmpty;
}