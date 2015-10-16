std::vector<Point*> heapsort( std::vector<Point*> data )
{

	int amountOfVals = data.size();
	int sortedNums = 0;

	while( sortedNums < amountOfVals )
	{

		Point* max = data.at(0);
		int maxAdr = 0;

		for( int i = 0; i < amountOfVals-sortedNums; i++ )
		{

			if( *data.at(i) > *max )
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