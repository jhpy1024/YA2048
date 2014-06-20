#include "Grid.hpp"
#include "Util.hpp"

#include <cmath>

Grid::Grid(const sf::Vector2f& position, const sf::Vector2f& size)
	: NUM_CELLS(4)
	, CELL_WIDTH(size.x / NUM_CELLS)
	, CELL_HEIGHT(size.y / NUM_CELLS)
	, CELL_PADDING(5.f)
	, m_Size(size)
	, m_Background(size)
	, m_CellShapes(NUM_CELLS, std::vector<sf::RectangleShape>(NUM_CELLS))
	, m_CellTexts(NUM_CELLS, std::vector<sf::Text>(NUM_CELLS))
	, m_Cells(NUM_CELLS, std::vector<int>(NUM_CELLS, 0))
	, m_GameOver(false)
{
	setPosition(position.x - CELL_PADDING * NUM_CELLS / 2, position.y);

	m_Font.loadFromFile("res/fonts/Ubuntu-M.ttf");

	m_Background.setFillColor(sf::Color(37, 179, 250, 255));

	initCellColors();
	createLines();
	createStartingCells();	
}

void Grid::moveUp()
{
	int numMoves = 0;

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

				++numMoves;
			}

			if ((highestY > 0) && (m_Cells[x][highestY] == m_Cells[x][highestY-1]))
			{
				m_Cells[x][highestY] = 0;
				m_Cells[x][highestY-1] *= 2;
			}
		}
	}

	if ((numMoves == 0) && (getFreeCells().size() == 0))
		m_GameOver = true;
	else
		createNewCell();
}

void Grid::moveDown()
{
	int numMoves = 0;

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

				++numMoves;
			}
			
			if ((lowestY < NUM_CELLS - 1) && (m_Cells[x][lowestY] == m_Cells[x][lowestY+1]))
			{
				m_Cells[x][lowestY] = 0;
				m_Cells[x][lowestY+1] *= 2;
			}
		}
	}

	if ((numMoves == 0) && (getFreeCells().size() == 0))
		m_GameOver = true;
	else
		createNewCell();
}

void Grid::moveLeft()
{
	int numMoves = 0;

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

				++numMoves;
			}

			if ((leftmostX > 0) && (m_Cells[leftmostX][y] == m_Cells[leftmostX-1][y]))
			{
				m_Cells[leftmostX][y] = 0;
				m_Cells[leftmostX-1][y] *= 2;
			}
		}
	}

	if ((numMoves == 0) && (getFreeCells().size() == 0))
		m_GameOver = true;
	else
		createNewCell();	
}

void Grid::moveRight()
{
	int numMoves = 0;

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

				++numMoves;
			}

			if ((rightmostX < NUM_CELLS - 1) && (m_Cells[rightmostX][y] == m_Cells[rightmostX+1][y]))
			{
				m_Cells[rightmostX][y] = 0;
				m_Cells[rightmostX+1][y] *= 2;
			}
		}
	}

	if ((numMoves == 0) && (getFreeCells().size() == 0))
		m_GameOver = true;
	else
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
			m_CellShapes[x][y].setPosition((CELL_WIDTH + CELL_PADDING) * x, (CELL_HEIGHT + CELL_PADDING) * y);
			m_CellShapes[x][y].setSize({ CELL_WIDTH, CELL_HEIGHT });

			m_CellShapes[x][y].setFillColor(m_CellColors[m_Cells[x][y]]);

			m_CellTexts[x][y].setFont(m_Font);
			m_CellTexts[x][y].setString((m_Cells[x][y] != 0 ? std::to_string(m_Cells[x][y]) : ""));
			m_CellTexts[x][y].setColor(sf::Color::Black);
			auto localBounds = m_CellTexts[x][y].getLocalBounds();
			m_CellTexts[x][y].setOrigin(localBounds.left + localBounds.width / 2.f, localBounds.top + localBounds.height / 2.f);

			auto tx = ((CELL_WIDTH + CELL_PADDING) * x) + (CELL_WIDTH / 2.f);
			auto ty = ((CELL_HEIGHT + CELL_PADDING) * y) + (CELL_HEIGHT / 2.f);

			m_CellTexts[x][y].setPosition(tx, ty);

			target.draw(m_CellShapes[x][y], states);
			target.draw(m_CellTexts[x][y], states);
		}
	}

	for (auto& line : m_Lines)
		target.draw(line, states);
}

void Grid::reset()
{
	m_GameOver = false;
	m_CellShapes = std::vector<std::vector<sf::RectangleShape>>(NUM_CELLS, std::vector<sf::RectangleShape>(NUM_CELLS));
	m_CellTexts = std::vector<std::vector<sf::Text>>(NUM_CELLS, std::vector<sf::Text>(NUM_CELLS));
	m_Cells = std::vector<std::vector<int>>(NUM_CELLS, std::vector<int>(NUM_CELLS, 0));

	createStartingCells();
}

bool Grid::isGameOver() const
{
	return m_GameOver;
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
	line.setFillColor(sf::Color(128, 128, 128));

	for (int i = 0; i < NUM_CELLS + 1; ++i)
	{
		// Vertical line
		line.setPosition(-CELL_PADDING + (CELL_WIDTH + CELL_PADDING) * i, -CELL_PADDING);
		line.setSize({ CELL_PADDING, m_Size.y + CELL_PADDING * NUM_CELLS });
		m_Lines.push_back(line);

		// Horizontal line
		line.setPosition(0.f, -CELL_PADDING + (CELL_HEIGHT + CELL_PADDING) * i);
		line.setSize({ m_Size.x + CELL_PADDING * NUM_CELLS, CELL_PADDING });
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
	m_CellColors[0] = sf::Color(32, 32, 32);
	m_CellColors[2] = sf::Color(85, 98, 112);
	m_CellColors[4] = sf::Color(78, 205, 196);
	m_CellColors[8] = sf::Color(199, 244, 100);
	m_CellColors[16] = sf::Color(255, 107, 107);
	m_CellColors[32] = sf::Color(196, 77, 88);
	m_CellColors[64] = sf::Color(73, 10, 61);
	m_CellColors[128] = sf::Color(189, 21, 80);
	m_CellColors[256] = sf::Color(233, 127, 2);
	m_CellColors[512] = sf::Color(248, 202, 0);
	m_CellColors[1024] = sf::Color(138, 155, 15);
	m_CellColors[2048] = sf::Color(255, 229, 69);
}