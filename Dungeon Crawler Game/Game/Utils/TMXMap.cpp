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

	//cout << map << endl;
	char* a = new char[map.size() + 1];
	strcpy_s(a, map.size() + 1, map.c_str());

	doc_.parse<0>(a);

	setupTileMap();

	/*
	cout << "\n\n\n" << doc_.first_node()->name() << endl;
	cout << doc_.first_node()->first_attribute()->name() << endl;
	cout << doc_.first_node()->first_attribute()->value() << endl;
	*/



	delete[] a;
	return(true);
}

string MTileMap::tmxToString(const string& filename)
{
	string map; //Will contain read in data from the .tmx
	ifstream fromMap;

	fromMap.open(filename, ios::in);

	if (fromMap.fail())
	{//failure to open file
		cout << "Error! Failed to open: " << filename << endl;
		return(" "); //Will cause loadMap to return false
	}
	else
	{
		string temp;
		while (!fromMap.eof()) //While not at the end of a line
		{//fill the temp string with data
			getline(fromMap, temp);
			map += temp; //and append it onto the map string
		}
	}

	return(map);
}

void MTileMap::setupTileMap()
{
	istringstream is;

	//Find the map node in TMX file
	xml_node<>* mapNode = doc_.first_node("map");
	//set the maps with to the value of this attibute
	is.str(mapNode->first_attribute("width")->value());
	is >> width_;

	is.clear();
	is.str(mapNode->first_attribute("height")->value());
	is >> height_; //set map height 

	is.clear();
	is.str(mapNode->first_attribute("tilewidth")->value());
	is >> tileWidth_;

	is.clear();
	is.str(mapNode->first_attribute("tileheight")->value());
	is >> tileHeight_;

	is.clear();
	{//TILESET INITIALISATION
		xml_node<>* tilesetNode = doc_.first_node("tileset");
		xml_node<>* tileNode = doc_.first_node("tile");

		int counter(0);

		while (tilesetNode)
		{
			tilesets_.push_back(new MTileset);
			//setting first grid
			is.clear();
			is.str(tilesetNode->first_attribute("firtgrid")->value());
			is >> tilesets_[counter]->firstGrid_;

			tilesets_[counter]->name_ = tilesetNode->first_attribute("name")->value();
			tilesets_[counter]->tileWidth_ = tileWidth_;
			tilesets_[counter]->tileHeight_ = tileHeight_;

			while (tileNode)
			{

			}



			++counter;
		}

	}//END OF TILESET INITIALISATION

}