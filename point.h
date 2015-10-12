#ifndef POINT_H
#define POINT_H

struct Coord
{

	Coord( float x, float y );
	Coord();

	float x, y;

};

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

class Point
{

	public:
		Point( int x, int y, int cost, Point *parent );
		Point();
		Point( int x, int y, int cost );

		Point *getParent();
		void  *setParent( Point *parent );

		Coord getPos();

		bool operator>( const &Point b ){ return (this->_cost > b->_cost); }

	private:
		Coord _pos;
		int _cost;
		Point *_parent;


};

#endif