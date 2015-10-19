#ifndef MOUSE_CPP
#define MOUSE_CPP

#include <GL/glfw3.h>
#include <vector>
#include <iostream>
#include <cmath>

#include "point.h"

Coord mousePos;
bool mouseLeft = false;
bool mouseRight = false;

float w = 16.0f;

std::vector< std::vector<int> > walls( 50, std::vector<int>(50) );

void mousePosCallBack( GLFWwindow *wind, double x, double y )
{

	mousePos.x = x;
	mousePos.y = y;

}

void mouseClickCallBack( GLFWwindow *wind, int button, int action, int mods )
{

	int bl, h;
	glfwGetWindowSize( glfwGetCurrentContext(), &bl, &h );

	if( button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS )
	{

		if( !mouseLeft )
		{

			walls[mousePos.x/w][(h-mousePos.y)/w]+=1;

		}

		mouseLeft = true;

	}else if( button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE )
	{

		mouseLeft = false;

	}

	if( button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS )
	{

		if( !mouseRight && walls[mousePos.x/w][(h-mousePos.y)/w] > 0 )
		{

			walls[mousePos.x/w][(h-mousePos.y)/w]-=1;


		}
		mouseRight = true;

	}else if( button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_RELEASE )
	{

		mouseRight = false;

	}

}

void ResetKeys()
{

	mouseLeft = false;
	mouseRight = false;

}

#endif