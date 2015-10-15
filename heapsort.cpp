#include <iostream>
#include <vector>
#include <cstdlib>

template<class T>
std::vector<T> heapsort( std::vector<T> data )
{

	int amountOfVals = data.size();
	int sortedNums = 0;

	while( sortedNums < amountOfVals )
	{

		T max = data.at(0);
		int maxAdr = 0;

		for( int i = 0; i < amountOfVals-sortedNums; i++ )
		{

			if( data.at(i) > max )
			{

				max = data.at(i);
				maxAdr = i;

			}

		}

		data.erase( data.begin()+maxAdr );
		data.insert( data.begin()+(amountOfVals-sortedNums-1), max );
		sortedNums++;

	}

	return data;

}