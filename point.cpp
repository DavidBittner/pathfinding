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

bool Point::operator>( Point const b ) const
{

	return( this->_cost > b._cost );

}

int Point::manhattanDistance( Coord pos )
{

	int x = abs( pos.x - _pos.x );
	int y = abs( pos.y - _pos.y );

	return x+y;

}