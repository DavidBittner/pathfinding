#include <GL/glfw3.h>
#include <iostream>

#include <vector>

#include "point.cpp"
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

void AStar( std::vector< std::vector< bool > > grid, Point start, Point end )
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

			cur = new Point( end.getPos().x, end.getPos().y, 0, cur );
			break;

		}

		for( int y = -1; y <= 1; y++ )
		{

			for( int x = -1; x <= 1; x++ )
			{

				int curX = cur->getPos().x+x;
				int curY = cur->getPos().y+y;

				Coord temp( curX, curY );

				bool make = true;

				for( int i = 0; i < open.size(); i++ )
				{

					if( temp == open.at(i)->getPos() )
					{

						make = false;

					}

				}

				for( int i = 0; i < closed.size(); i++ )
				{

					if( temp == closed.at(i)->getPos() )
					{

						make = false;

					}

				}

				if( make )
				{
		
					open.push_back( new Point( curX, curY, manhattan( cur->getPos(), temp ), cur ) );

				}
		
			}

		}

		closed.push_back( open.at(0) );
		open.erase( open.begin() );

		open = heapsort( open );

	}

}

int main()
{

	std::vector< std::vector< bool > > a;

	Point start( 1, 1, 0, nullptr );
	Point end( 5, 1, 0, nullptr );

	AStar( a, start, end );

	glfwInit();
	GLFWwindow *wind = glfwCreateWindow( 800, 600, "A* Pathfinding", nullptr, nullptr );

	glfwMakeContextCurrent( wind );
	Reshape( wind, 800, 600 );

	glfwSetWindowSizeCallback( wind, Reshape );

	while( !glfwWindowShouldClose( wind ) )
	{

		glClear( GL_COLOR_BUFFER_BIT );
		glLoadIdentity();

		glTranslatef( 0.0f, 0.0f, -1.0f );

		glfwPollEvents();
		glfwSwapBuffers( wind );

	}

	glfwTerminate();

}