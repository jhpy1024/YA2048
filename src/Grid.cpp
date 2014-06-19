#include "Grid.hpp"
#include "Util.hpp"

#include <cmath>

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

	initCellColors();
	createLines();
	createStartingCells();	
}

void Grid::moveUp()
{
	for (int x = 0; x < NUM_CELLS; ++x)
	{
		for (int y = 1; y < NUM_CELLS; ++y)
		{
			if (m_Cells[x][y] == 0)
				continue;

			int highestY = y;
			for (int i = y; i >= 0; --i)
			{
				if (m_Cells[x][i] == 0 && i < highestY)
					highestY = i;
			}

			if (highestY != y)
			{
				m_Cells[x][highestY] = m_Cells[x][y];
				m_Cells[x][y] = 0;
			}

			if ((highestY > 0) && (m_Cells[x][highestY] == m_Cells[x][highestY-1]))
			{
				m_Cells[x][highestY] = 0;
				m_Cells[x][highestY-1] *= 2;
			}
		}
	}

	createNewCell();
}

void Grid::moveDown()
{
	for (int x = 0; x < NUM_CELLS; ++x)
	{
		for (int y = NUM_CELLS - 2; y >= 0; --y)
		{
			if (m_Cells[x][y] == 0)
				continue;

			int lowestY = y;
			for (int i = y; i < NUM_CELLS; ++i)
			{
				if (m_Cells[x][i] == 0 && i > lowestY)
					lowestY = i;
			}

			if (lowestY != y)
			{
				m_Cells[x][lowestY] = m_Cells[x][y];
				m_Cells[x][y] = 0;

			}
			
			if ((lowestY < NUM_CELLS - 1) && (m_Cells[x][lowestY] == m_Cells[x][lowestY+1]))
			{
				m_Cells[x][lowestY] = 0;
				m_Cells[x][lowestY+1] *= 2;
			}
		}
	}

	createNewCell();
}

void Grid::moveLeft()
{
	for (int x = 1; x < NUM_CELLS; ++x)
	{
		for (int y = 0; y < NUM_CELLS; ++y)
		{
			if (m_Cells[x][y] == 0)
				continue;

			int leftmostX = x;
			for (int i = x; i >= 0; --i)
			{
				if (m_Cells[i][y] == 0 && i < leftmostX)
					leftmostX = i;
			}

			if (leftmostX != x)
			{
				m_Cells[leftmostX][y] = m_Cells[x][y];
				m_Cells[x][y] = 0;
			}

			if ((leftmostX > 0) && (m_Cells[leftmostX][y] == m_Cells[leftmostX-1][y]))
			{
				m_Cells[leftmostX][y] = 0;
				m_Cells[leftmostX-1][y] *= 2;
			}
		}
	}

	createNewCell();	
}

void Grid::moveRight()
{
	for (int x = NUM_CELLS - 2; x >= 0; --x)
	{
		for (int y = 0; y < NUM_CELLS; ++y)
		{
			if (m_Cells[x][y] == 0)
				continue;

			int rightmostX = x;
			for (int i = x; i < NUM_CELLS; ++i)
			{
				if (m_Cells[i][y] == 0 && i > rightmostX)
					rightmostX = i;
			}

			if (rightmostX != x)
			{
				m_Cells[rightmostX][y] = m_Cells[x][y];
				m_Cells[x][y] = 0;
			}

			if ((rightmostX < NUM_CELLS - 1) && (m_Cells[rightmostX][y] == m_Cells[rightmostX+1][y]))
			{
				m_Cells[rightmostX][y] = 0;
				m_Cells[rightmostX+1][y] *= 2;
			}
		}
	}

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

			auto value = m_Cells[x][y];
			m_CellShapes[x][y].setFillColor(m_CellColors[value]);

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

void Grid::initCellColors()
{
	m_CellColors[2] = sf::Color::Green;
	m_CellColors[4] = sf::Color::Yellow;
	m_CellColors[8] = sf::Color::Blue;
	m_CellColors[16] = sf::Color::Red;
	m_CellColors[32] = sf::Color::Cyan;
	m_CellColors[64] = sf::Color::Magenta;
	m_CellColors[128] = sf::Color(102, 0, 102); // purple-ish
	m_CellColors[256] = sf::Color(255, 128, 0); // orange-ish
	m_CellColors[512] = sf::Color(255, 153, 153); // light-red-ish
	m_CellColors[1024] = sf::Color(255, 153, 204); // light-pink-ish
	m_CellColors[2048] = sf::Color::Yellow;
}