#include <GL/glfw3.h>
#include <iostream>

#include <vector>

#include "point.cpp"

void Reshape( GLFWwindow *wind, int width, int height )
{

	glViewport( 0, 0, (GLsizei)width, (GLsizei)height );
	glMatrixMode( GL_PROJECTION );

	glLoadIdentity();

	glOrtho( 0, width, 0, height, 1.0f, 10.0f );
	glMatrixMode( GL_MODELVIEW );

}

void AStar( std::vector< std::vector< Point > > grid, Point start, Point end )
{

	Point *cur = &start;

	std::vector< Point > closed;
	std::vector< Point > open;

	open.push_back( start );

	while( cur->getPos() != end.getPos() )
	{



	}

}

int main()
{

	Point test( 0, 0, 0, nullptr );

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