#ifndef MAPDRAW_H
#define MAPDRAW_H

void DrawPath( std::vector<Coord> in )
{

	std::vector<float> coords;
	std::vector<float> colors;

	for( int i = 0; i < in.size(); i++ )
	{

		int posX = in.at( i ).x*w;
		int posY = in.at( i ).y*w;

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

void DrawMap()
{

	std::vector<float> coords;
	std::vector<float> colors;

	for( int y = 0; y < walls.size(); y++ )
	{

		for( int x = 0; x < walls[y].size(); x++ )
		{

			int posX = (x*w);
			int posY = (y*w);

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

				colors.push_back( walls[x][y]/10.0f );
				colors.push_back( walls[x][y]/10.0f );
				colors.push_back( walls[x][y]/10.0f );

			}

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

#endif