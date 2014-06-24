#ifndef GRID_HPP
#define GRID_HPP

#include <SFML/Graphics.hpp>
#include <vector>
#include <map>

class Grid : public sf::Drawable, public sf::Transformable
{
public:
	Grid(const sf::Vector2f& position, const sf::Vector2f& size);

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	void moveUp();
	void moveDown();
	void moveLeft();
	void moveRight();

	bool isGameOver() const;

	void reset(std::string type);

	int getScore() const;

private:
	void initCellColors();
	void initCellShapes();

	void createLines();
	void createVerticalLine(int column);
	void createHorizontalLine(int row);

	void createStartingCells();
	void createNewCell();
	std::vector<sf::Vector2f> getFreeCells() const;

	int getRightmostCellFrom(int x, int y) const;
	int getLeftmostCellFrom(int x, int y) const;
	int getHighestCellFrom(int x, int y) const;
	int getLowestCellFrom(int x, int y) const;

	void moveCell(int x, int y, int x1, int y1);
	void combineCells(int x, int y, int x1, int y1);

	void drawBackground(sf::RenderTarget& target, sf::RenderStates states) const;
	void drawLines(sf::RenderTarget& target, sf::RenderStates states) const;
	void drawCells(sf::RenderTarget& target, sf::RenderStates states) const;
	void drawCellsText(sf::RenderTarget& target, sf::RenderStates states) const;
	void drawAnimShapes(sf::RenderTarget& target, sf::RenderStates states) const;

	bool isCellEmpty(int x, int y) const;
	bool cellsEqual(int x, int y, int x1, int y1) const;
	bool isGridFull() const;

	sf::Vector2f tileToWorld(const sf::Vector2f& pos) const;
	sf::Vector2f worldToTile(const sf::Vector2f& pos) const;

	void createAnimation(const sf::Vector2f& start, const sf::Vector2f& end);
	void updateCombineAnimation() const;

	void completeMove(int numMoves);

private:
	const int NUM_CELLS;
	const float CELL_WIDTH;
	const float CELL_HEIGHT;
	const float CELL_PADDING;

	sf::Vector2f m_Size;

	sf::RectangleShape m_Background;
	std::vector<sf::RectangleShape> m_Lines;

	mutable std::vector<std::vector<sf::RectangleShape>> m_CellShapes;
	mutable std::map<int, sf::Color> m_CellColors;

	sf::Font m_Font;
	mutable std::vector<std::vector<sf::Text>> m_CellTexts;

	std::vector<std::vector<int>> m_Cells;

	bool m_GameOver;

	int m_Score;

	struct AnimData {
		sf::Vector2f start;
		sf::Vector2f end;

		AnimData(const sf::Vector2f& start, const sf::Vector2f& end)
			: start(start), end(end)
		{}
	};
	mutable std::vector<std::pair<AnimData, sf::RectangleShape>> m_AnimShapes;

	mutable std::vector<std::vector<bool>> m_IsCombining;
};

#endif
