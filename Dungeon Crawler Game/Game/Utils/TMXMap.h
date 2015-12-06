
#ifndef TMXMAP_H
#define TMXMAP_H
#include <iostream> 
#include <vector> 
#include <string> 
#include <fstream>
#include <sstream>
#include <assert.h>
#include "..\RapidXML\rapidxml.hpp"

using namespace std;
using namespace rapidxml;

struct MOBjectProperty
{//Object property
	string name;
	string value;
};

struct MTileProperty : MOBjectProperty
{//Tile property
};

struct MTile
{
	MTileProperty prop;
	int id;
};
struct MTileset
{//Map Tileset
	string name_;
	string fileName_;
	int tileWidth_;
	int tileHeight_;
	int tileCount_;
	int firstgid_;
	vector<MTile>tile;
};

class MLayer
{
public:
	string name;
	int width;
	int height;
	std::vector<int> data;
};




struct MObject
{

};

class MTileMap
{
public:
	~MTileMap();
	const vector<MTileset*>& getTilesets() const;
	bool loadMap(const std::string&);
	int getWidth() const { return width_; }
	int getHeight() const { return height_; }
	int getTileWidth() const { return tileWidth_; }
	int getTileHeight() const{ return tileHeight_; }
private:
	string tmxToString(const std::string&);
	void setupTileMap();
	void setupTilesets(xml_node<>*);
	void setupLayer(xml_node<>*);
	int width_;  //Map width
	int height_; //Map height
	int tileWidth_;
	int tileHeight_;
	vector <MTileset*> tilesets_;
	vector <MLayer*> layers_;
	xml_document<> doc_;

};

#endif
