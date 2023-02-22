#pragma once
class Grid
{
private:

protected:

public:
	int x;
	int y;
	Grid() {
		x = 0;
		y = 0;
	}
	Grid(int m_x, int m_y) {
		x = m_x;
		y = m_y;
	}
	bool operator ==(Grid &g1) {
		if (x == g1.x && y == g1.y)
			return true;
		return false;
	}
};

