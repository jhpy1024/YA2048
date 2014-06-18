#include "Grid.hpp"
#include "Util.hpp"

#include <iostream>

Grid::Grid(const sf::Vector2f& position, const sf::Vector2f& size)
	: NUM_CELLS(4)
	, CELL_WIDTH(size.x / NUM_CELLS)
	, CELL_HEIGHT(size.y / NUM_CELLS)
	, m_Size(size)
	, m_Background(size)
	, m_CellShapes(NUM_CELLS, std::vector<sf::RectangleShape>(NUM_CELLS))
	, m_CellTexts(NUM_CELLS, std::vector<sf::Text>(NUM_CELLS))
	, m_Cells(NUM_CELLS, std::vector<int>(NUM_CELLS, 0))
{
	setPosition(position);

	m_Font.loadFromFile("res/fonts/Ubuntu-M.ttf");

	m_Background.setFillColor(sf::Color(37, 179, 250, 255));

	createLines();
	createStartingCells();	
}

void Grid::moveUp()
{
	

	createNewCell();
}

void Grid::moveDown()
{
	

	createNewCell();
}

void Grid::moveLeft()
{
	

	createNewCell();	
}

void Grid::moveRight()
{
	

	createNewCell();
}

void Grid::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();

	target.draw(m_Background, states);

	for (int x = 0; x < NUM_CELLS; ++x)
	{
		for (int y = 0; y < NUM_CELLS; ++y)
		{
			m_CellShapes[x][y].setPosition(CELL_WIDTH * x, CELL_HEIGHT * y);
			m_CellShapes[x][y].setSize({ CELL_WIDTH, CELL_HEIGHT });
			m_CellShapes[x][y].setFillColor((m_Cells[x][y] == 0 ? sf::Color::Black : sf::Color::Red));
			if (m_Cells[x][y] == 2) m_CellShapes[x][y].setFillColor(sf::Color::Green);

			m_CellTexts[x][y].setFont(m_Font);
			m_CellTexts[x][y].setPosition(CELL_WIDTH * x, CELL_HEIGHT * y);
			m_CellTexts[x][y].setString((m_Cells[x][y] != 0 ? std::to_string(m_Cells[x][y]) : ""));
			m_CellTexts[x][y].setColor(sf::Color::Black);

			target.draw(m_CellShapes[x][y], states);
			target.draw(m_CellTexts[x][y], states);
		}
	}

	for (auto& line : m_Lines)
		target.draw(line, states);
}

void Grid::createNewCell()
{
	auto availableCells = getFreeCells();
	auto randIndex = Random::genInt(0, availableCells.size() - 1);
	auto cellPos = availableCells[randIndex];

	m_Cells[cellPos.x][cellPos.y] = 2;
}

std::vector<sf::Vector2f> Grid::getFreeCells() const
{
	std::vector<sf::Vector2f> freeCells;

	for (int x = 0; x < NUM_CELLS; ++x)
	{
		for (int y = 0; y < NUM_CELLS; ++y)
		{
			if (m_Cells[x][y] == 0)
				freeCells.push_back({ static_cast<float>(x), static_cast<float>(y) });
		}
	}

	return freeCells;
}

void Grid::createLines()
{
	sf::RectangleShape line;
	line.setFillColor(sf::Color(133, 214, 255, 255));

	for (int i = 0; i < NUM_CELLS + 1; ++i)
	{
		// Vertical line
		line.setPosition(CELL_WIDTH * i, 0.f);
		line.setSize({ 1.f, m_Size.y });
		m_Lines.push_back(line);

		// Horizontal line
		line.setPosition(0.f, CELL_HEIGHT * i);
		line.setSize({ m_Size.x, 1.f });
		m_Lines.push_back(line);
	}
}

void Grid::createStartingCells()
{
	for (int i = 0; i < 2; ++i)
		createNewCell();
}