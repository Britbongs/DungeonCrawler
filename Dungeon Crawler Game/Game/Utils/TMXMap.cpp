#include "TMXMap.h"

MTileMap::~MTileMap()
{

}

bool MTileMap::loadMap(const string& filename)
{
	assert(filename.size() > 3);

	std::string map = tmxToString(filename);
	if (map.size() < 1)
		return(false);

	cout << map << endl;

	return(true);
}

string MTileMap::tmxToString(const string& filename)
{
	string map;
	ifstream fromMap;
	fromMap.open(filename, ios::in);

	if (fromMap.fail())
	{
		cout << "Error! Failed to open: " << filename << endl;
		return(" "); //Will cause loadMap to return false
	}
	else
	{
		string temp;
		while (!fromMap.eof())
		{
			getline(fromMap, temp);
			map += temp;
		}
	}

	return(map);
}