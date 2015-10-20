#include <GL/glfw3.h>
#include <iostream>

#include <vector>
#include <chrono>
#include <thread>

#include "mouse.cpp"
#include "point.h"
#include "heapsort.cpp"
#include "draw.cpp"

void Reshape( GLFWwindow *wind, int width, int height )
{

	glViewport( 0, 0, (GLsizei)width, (GLsizei)height );
	glMatrixMode( GL_PROJECTION );

	glLoadIdentity();

	glOrtho( 0, width, 0, height, 1.0f, 10.0f );
	glMatrixMode( GL_MODELVIEW );

}

int manhattan( Coord a, Coord b )
{

	int x = abs(b.x-a.x);
	int y = abs(b.y-a.y);
	return x+y;

}

std::vector<Coord> AStar( std::vector< std::vector< int > > grid, Point start, Point end )
{

	//The current 'focal' point.
	Point *cur;

	//The open and closed lists.
	std::vector< Point* > closed;
	std::vector< Point* > open;

	//Start by adding the starting position to the list.
	open.push_back( &start );

	//Just so it knows whether or not to try and reconstruct a path.
	bool error = true;

	while( open.size() > 0 )
	{

		//The current point is the first entry in the open list.
		cur = open.at(0);

		if( cur->getPos() == end.getPos() )
		{

			error = false;
			break;

		}

		//Add in all the neighbors of the current point.
		for( int y = -1; y <= 1; y++ )
		{

			for( int x = -1; x <= 1; x++ )
			{

				int curX = cur->getPos().x+x;
				int curY = cur->getPos().y+y;

				int movCost = 10;

				//If it is a diagonal, make it cost 14 instead of 10.
				if( (y == -1 && x == -1)||
					(y ==  1 && x == -1)||
					(y == -1 && x ==  1)||
					(y ==  1 && x ==  1))
				{

					movCost = 14;
					//continue;

				}

				Coord temp( curX, curY );
				bool make = true;

				//If it is outside the range of the map, continue.
				if( curY >= grid.size() || 
					curX >= grid.size() )
				{

					continue;
				}

				/*

				These two loops are to check whether or not the point's neighbors already exist.
				This feels really sloppy to me. Please tell me if there is a better way.

				*/
				for( int i = 0; i < open.size(); i++ )
				{

					if( temp == open.at(i)->getPos() )
					{

						make = false;
						break;

					}

				}

				for( int i = 0; i < closed.size(); i++ )
				{

					if( temp == closed.at(i)->getPos() )
					{

						make = false;
						break;

					}

				}

				//If the point in the map is a zero, then it is a wall. Continue.
				if( (grid.at(temp.x).at(temp.y) == 0 ) ||
					( temp.x<0 || temp.y < 0 ) )
				{

					continue;

				}

				//If it is allowed to make a new point, it adds it to the open list.
				if( make )
				{

					int gScore = cur->getCost();
					int hScore = manhattan( end.getPos(), Coord( curX, curY ) );
					int tileCost = grid[curX][curY];
					int fScore = gScore+hScore+tileCost+movCost;

					open.push_back( new Point( curX, curY, fScore, cur ) );

				}
		
			}

		}

		//It then pushes back the current into the closed set as well as erasing it from the open set.
		closed.push_back( cur );
		open.erase( open.begin() );

		//Heapsort works, guranteed. Not sure if it's a stable sort, though. From what I can tell that shouldn't matter, though.
		open = heapsort( open );

	}

	std::vector<Coord> path;

	if( error )
	{

		return path;

	}

	//Reconstruct a path by tracing through the parents.
	while( cur->getParent() != nullptr )
	{

		path.push_back( cur->getPos() );
		cur = cur->getParent();
		
	}

	path.push_back( cur->getPos() );

	return path;

}

int main()
{

	std::vector< Coord > path;
	
	Point *start = new Point( 5, 1, 0, nullptr );
	Point *end = new Point( 5, 15, 0, nullptr );

	glfwInit();
	DrawPath( path );
	GLFWwindow *wind = glfwCreateWindow( 800, 600, "A* Pathfinding", nullptr, nullptr );

	glfwMakeContextCurrent( wind );
	Reshape( wind, 800, 600 );

	glfwSetWindowSizeCallback( wind, Reshape );
	glfwSetCursorPosCallback( wind, mousePosCallBack );
	glfwSetMouseButtonCallback( wind, mouseClickCallBack );

	srand( time(nullptr) );

	for( int y = 0; y < walls.size(); y++ )
	{

		for( int x = 0; x < walls[y].size(); x++ )
		{

			walls[x][y] = 1;

		}

	}

	while( !glfwWindowShouldClose( wind ) )
	{

		glClear( GL_COLOR_BUFFER_BIT );
		glLoadIdentity();

		glTranslatef( 0.0f, 0.0f, -1.0f );

		path = AStar( walls, *start, *end );
		DrawMap();
		DrawPath( path );

		std::this_thread::sleep_for( std::chrono::milliseconds(17) );

		//ResetKeys();
		glfwPollEvents();
		glfwSwapBuffers( wind );

	}

	glfwTerminate();

}