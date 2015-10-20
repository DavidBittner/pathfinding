#ifndef POINT_H
#define POINT_H

struct Coord
{

	Coord( float x, float y );
	Coord();

	float x, y;

	bool operator!=( Coord const b ) const
	{

		return ( this->x == b.x && this->y == b.y );

	}

	bool operator==( Coord const b ) const
	{

		return( this->x == b.x && this->y == b.y );

	}

};

class Point
{

	public:
		Point( int x, int y, int cost, Point *parent );
		Point();
		Point( int x, int y, int cost );

		Point *getParent(){ return _parent; }
		void  *setParent( Point *parent ){ _parent = parent; }

		Coord getPos(){ return _pos; }
		int getCost(){ return _cost; }

		bool operator>( Point const b ) const;
		bool operator<( Point const b ) const;
		bool operator>=( Point const b ) const;

	private:
		Coord _pos;
		int _cost;
		Point *_parent;


};

#endif