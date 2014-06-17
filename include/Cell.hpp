#ifndef CELL_HPP
#define CELL_HPP

#include <SFML/Graphics.hpp>

class Cell : public sf::Drawable, public sf::Transformable
{
public:
	Cell(const sf::Vector2f& position, const sf::Vector2f& size);

	void combine(Cell& cell);

	int getValue() const; 
	bool isEmpty() const;

	void setEmpty();
	void setValue(int value);

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
	static sf::Font m_Font;

	sf::RectangleShape m_Shape;
	sf::Text m_Text;

	int m_Value;
	bool m_IsEmpty;
};

#endif