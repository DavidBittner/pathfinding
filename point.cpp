#include "point.h"

Point::Point( int x, int y, int cost, Point *parent )
{

	_pos.x = x;
	_pos.y = y;

	_cost = cost;

	_parent = parent;

}

Point::Point()
{

	_pos.x = 0;
	_pos.y = 0;

	_cost = 1;

	_parent = nullptr;

}

Point::Point( int x, int y, int cost )
{

	_pos.x = x;
	_pos.y = y;

	_cost = cost;

	_parent = nullptr;

}
