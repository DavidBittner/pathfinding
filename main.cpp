#include <GL/glfw3.h>
#include <iostream>

#include <vector>
#include <chrono>
#include <thread>

#include "point.h"
#include "heapsort.cpp"

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

void DrawPath( std::vector<Coord> in )
{

	std::vector<float> coords;
	std::vector<float> colors;
	float w = 32;

	for( int i = 0; i < in.size(); i++ )
	{

		int posX = in.at( i ).x*32;
		int posY = in.at( i ).y*32;

		coords.push_back( posX );
		coords.push_back( posY );

		coords.push_back( posX+w );
		coords.push_back( posY );

		coords.push_back( posX+w );
		coords.push_back( posY+w );

		coords.push_back( posX );
		coords.push_back( posY+w );

		for( int j = 0; j < 4; j++ )
		{

			colors.push_back( 0.4f );
			colors.push_back( 0.4f );
			colors.push_back( 0.4f );

		}
	}

	glEnableClientState( GL_VERTEX_ARRAY );
	glEnableClientState( GL_COLOR_ARRAY );

	glVertexPointer( 2, GL_FLOAT, 0, coords.data() );
	glColorPointer( 3, GL_FLOAT, 0, colors.data() );
	glDrawArrays( GL_QUADS, 0, coords.size()/2 );

	glDisableClientState( GL_COLOR_ARRAY );
	glDisableClientState( GL_VERTEX_ARRAY );

	coords.clear();
	colors.clear();

}

std::vector<Coord> AStar( std::vector< std::vector< bool > > grid, Point start, Point end )
{

	Point *cur;

	std::vector< Point* > closed;
	std::vector< Point* > open;

	open.push_back( &start );

	while( open.size() > 0 )
	{

		cur = open.at(0);

		if( cur->getPos() == end.getPos() )
		{

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

					movCost = 14;

				}

				Coord temp( curX, curY );

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

				if( grid.at(temp.x).at(temp.y) )
				{

					continue;

				}

				if( make )
				{
		
					open.push_back( new Point( temp.x, temp.y, manhattan( start.getPos(), temp )+manhattan( end.getPos(), temp )+movCost, cur ) );

				}
		
			}

		}

		closed.push_back( cur );
		open.erase( open.begin() );

		open = heapsort( open );
	
	}

	std::vector<Coord> path;

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

	std::vector<std::vector<bool>> map( 500, std::vector<bool>(500) );
	std::vector< Coord > path;
	
	Point *start = new Point( 5, 1, 0, nullptr );
	Point *end = new Point( 5, 15, 0, nullptr );

	for( int i = 0; i < 150; i++ )
	{

		map.at(i).at(10) = true;

	}

	path = AStar( map, *start, *end );

	glfwInit();
	DrawPath( path );
	GLFWwindow *wind = glfwCreateWindow( 800, 600, "A* Pathfinding", nullptr, nullptr );

	glfwMakeContextCurrent( wind );
	Reshape( wind, 800, 600 );

	glfwSetWindowSizeCallback( wind, Reshape );

	srand( time(nullptr) );

	while( !glfwWindowShouldClose( wind ) )
	{

		DrawPath( path );
		glClear( GL_COLOR_BUFFER_BIT );
		glLoadIdentity();

		glTranslatef( 0.0f, 0.0f, -1.0f );
		
		DrawPath( path );

		std::this_thread::sleep_for( std::chrono::milliseconds(17) );

		glfwPollEvents();
		glfwSwapBuffers( wind );

	}

	glfwTerminate();

}