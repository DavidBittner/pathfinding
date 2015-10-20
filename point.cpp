#include <cmath>
#include "point.h"

Coord::Coord( float x, float y )
{

	this->x = x;
	this->y = y;

}

Coord::Coord()
{

	this->x = 0;
	this->y = 0;

}

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

bool Point::operator<( Point const b ) const
{

	return( this->_cost < b._cost );

}

bool Point::operator>=( Point const b ) const
{

	return( this->_cost >= b._cost );

}