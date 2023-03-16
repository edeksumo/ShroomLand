#pragma once
class GridCell
{
private:

protected:

public:
	int x;
	int y;
	GridCell() {
		x = 0;
		y = 0;
	}
	GridCell(int m_x, int m_y) {
		x = m_x;
		y = m_y;
	}
	bool operator ==(GridCell &g1) {
		if (x == g1.x && y == g1.y)
			return true;
		return false;
	}
};

