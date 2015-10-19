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

	Point *cur;

	std::vector< Point* > closed;
	std::vector< Point* > open;

	open.push_back( &start );

	bool error = true;

	while( open.size() > 0 )
	{

		cur = open.at(0);

		if( cur->getPos() == end.getPos() )
		{

			error = false;
			break;

		}

		for( int y = -1; y <= 1; y++ )
		{

			for( int x = -1; x <= 1; x++ )
			{

				int curX = cur->getPos().x+x;
				int curY = cur->getPos().y+y;

				int movCost = 10;

				if( (y == -1 && x == -1)||
					(y ==  1 && x == -1)||
					(y == -1 && x ==  1)||
					(y ==  1 && x ==  1))
				{

					movCost = 10;

				}

				Coord temp( curX, curY );

				if( curY >= grid.size() )
				{

					continue;

				}

				if( curX >= grid[0].size() )
				{

					continue;

				}

				bool make = true;

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

				if( temp.x < 0 || temp.y < 0 )
				{

					continue;

				}

				if( grid.at(temp.x).at(temp.y) == 0 )
				{

					continue;

				}

				if( make )
				{
		
					open.push_back( new Point( temp.x, temp.y, manhattan( end.getPos(), temp )+movCost+grid[temp.x][temp.y], cur ) );

				}
		
			}

		}

		closed.push_back( cur );
		open.erase( open.begin() );

		open = heapsort( open );
	
	}

	std::vector<Coord> path;

	if( error )
	{

		return path;

	}

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
	Point *end = new Point( 25, 15, 0, nullptr );

	path = AStar( walls, *start, *end );

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