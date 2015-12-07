#include "TMXMap.h"

MTileMap::~MTileMap()
{
	for (size_t i(0); i < tilesets_.size(); ++i)
		delete tilesets_[i];

	for (size_t i(0); i < layers_.size(); ++i)
		delete layers_[i];
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

	setupTilesets(mapNode);

	setupLayer(mapNode);

}

void MTileMap::setupTilesets(xml_node<>* mapNode)
{
	istringstream is;

	xml_node<>* tilesetNode = mapNode->first_node("tileset"); //the note which contains the details of tilesets
	xml_node<>* tileNode = tilesetNode->first_node("tile"); //tile information node

	int counter(0);

	while (tilesetNode)
	{
		tilesets_.push_back(new MTileset);
		//setting first grid
		is.clear();
		is.str(tilesetNode->first_attribute("firstgid")->value());
		is >> tilesets_[counter]->firstgid_; //set the tilsets first grid value

		tilesets_[counter]->name_ = tilesetNode->first_attribute("name")->value(); // set the tiles name
		tilesets_[counter]->tileWidth_ = tileWidth_; //set tileWidth for the tileset
		tilesets_[counter]->tileHeight_ = tileHeight_; //set tileHeight for the tileset
		
		is.clear();
		is.str(tilesetNode->first_attribute("tilecount")->value());
		is >> tilesets_[counter]->tileCount_;


		while (tileNode)
		{//initialising the tile properties for each tileset
			MTile t;

			is.clear();
			is.str(tileNode->first_attribute("id")->value());
			is >> t.id;

			xml_node<>* tileProp = tileNode->first_node("properties")->first_node("property");

			while (tileProp)
			{

				t.prop.name = tileProp->first_attribute("name")->value();
				t.prop.value = tileProp->first_attribute("value")->value();

				tileProp = tileProp->next_sibling("property");
			}

			tilesets_[counter]->tile.push_back(t);
			tileNode = tileNode->next_sibling("tile");
		}



		++counter;
		tilesetNode = tilesetNode->next_sibling("tileset");
	}
	cout << tilesets_[0]->tile.size() << endl;
	for (size_t i(0); i < tilesets_[0]->tile.size(); ++i)
	{
		cout << "For tile " << i << " the property is: \n" << tilesets_[0]->tile[i].prop.name << " - " << tilesets_[0]->tile[i].prop.value << endl;
	}
}

void MTileMap::setupLayer(xml_node<>* mapNode)
{
	xml_node<>* layerNode = mapNode->first_node("layer");  //XML Node containing layer data
	istringstream is;

	int counter(0);

	while (layerNode != nullptr)
	{
		layers_.push_back(new MLayer);

		layers_[counter]->name = layerNode->first_attribute("name")->value();

		is.str(layerNode->first_attribute("width")->value());
		is >> layers_[counter]->width;

		is.clear();
		is.str(layerNode->first_attribute("height")->value());
		is >> layers_[counter]->height;

		string layerData = layerNode->first_node("data")->value(); //get the map data from the layer
		vector<int> a(height_); //a temporary vector we'll use as an example, will be pushed into a vector
		int stringCounter(0); //Used to keep track of where in the string layerData we're looking 

		cout << "\n\n\n";

		for (size_t i(0); i < width_; ++i)
		{
			
			layers_[counter]->data.push_back(a);
			
			for (size_t j(0); j < height_; ++j)
			{

				layers_[counter]->data[i].at(j) = (layerData[stringCounter] - '0'); //convert to integer
				++stringCounter;
				char c = layerData[stringCounter];
				++stringCounter;

				cout << layers_[counter]->data[i].at(j);
			}
			cout << endl;
		}


		layerNode = layerNode->next_sibling("layer");
		++counter;
	}

}
