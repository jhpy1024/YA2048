#include "Grid.hpp"

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

	sf::RectangleShape line;
	line.setFillColor(sf::Color(133, 214, 255, 255));

	for (int i = 0; i < NUM_CELLS + 1; ++i)
	{
		// Vertical line
		line.setPosition(CELL_WIDTH * i, 0.f);
		line.setSize({ 1.f, size.y });
		m_Lines.push_back(line);

		// Horizontal line
		line.setPosition(0.f, CELL_HEIGHT * i);
		line.setSize({ size.x, 1.f });
		m_Lines.push_back(line);
	}

	for (int i = 0; i < 2; ++i)
	{
		bool createdCell = false;

		while (!createdCell)
		{
			int x = rand() % NUM_CELLS;
			int y = rand() % NUM_CELLS;

			if (m_Cells[x][y] == 0)
			{
				m_Cells[x][y] = 2;
				createdCell = true;
			}
		}
	}
}

void Grid::moveUp()
{
	for (int x = 0; x < NUM_CELLS; ++x)
	{
		for (int y = 0; y < NUM_CELLS; ++y)
		{
			// Find the highest point this cell can be moved down to
			int newY = y;
			for (int i = y; i >= 0; --i)
			{
				if ((m_Cells[x][i] == 0) && (i < newY))
					newY = i;
			}

			// Move the cell up to the highest point it can go
			if (y != 0 && (m_Cells[x][y] != 0))
			{
				m_Cells[x][newY] = m_Cells[x][y];
				m_Cells[x][y] = 0;
			}

			// Combine tiles if necessary
			if (newY != 0 && (m_Cells[x][newY] == m_Cells[x][newY-1]))
			{
				m_Cells[x][newY-1] += m_Cells[x][newY];
				m_Cells[x][newY] = 0;
			}
		}
	}
}

void Grid::moveDown()
{
	for (int x = 0; x < NUM_CELLS; ++x)
	{
		for (int y = NUM_CELLS - 1; y >= 0; --y)
		{
			// Find the lowest point this cell can be moved down to
			int newY = y;
			for (int i = y; i < NUM_CELLS; ++i)
			{
				if ((m_Cells[x][i] == 0) && (i > newY))
					newY = i;
			}

			// Move the cell down to the lowest point it can go
			if (y != (NUM_CELLS - 1) && (m_Cells[x][y] != 0))
			{
				m_Cells[x][newY] = m_Cells[x][y];
				m_Cells[x][y] = 0;
			}

			// Combine tiles if necessary
			if (newY != (NUM_CELLS - 1) && (m_Cells[x][newY] == m_Cells[x][newY+1]))
			{
				m_Cells[x][newY+1] += m_Cells[x][newY];
				m_Cells[x][newY] = 0;
			}
		}
	}
}

void Grid::moveLeft()
{

}

void Grid::moveRight()
{

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