#include "TiledMap.h"
TiledMap::TiledMap()
	: currentTMXMap_(nullptr)
{

}
TiledMap::TiledMap(Map* tmxMap)
	: currentTMXMap_(tmxMap)
{
}

TiledMap::~TiledMap()
{
}

bool TiledMap::initaliseMap()
{
	if (currentTMXMap_)
	{
		mapBounds_.x = static_cast<unsigned> (currentTMXMap_->getWidth());
		mapBounds_.y = static_cast<unsigned> (currentTMXMap_->getHeight());
		tileSize_.x = static_cast<unsigned> (currentTMXMap_->getTileWidth());
		tileSize_.y = static_cast<unsigned> (currentTMXMap_->getTileHeight());

		firstGID_.resize(currentTMXMap_->getTileSet().size());
		tileCount_.resize(currentTMXMap_->getTileSet().size());

		for (int i(0); i < firstGID_.size(); ++i)
		{
			firstGID_[i] = currentTMXMap_->getTileSet()[i]->firstgid_;
			tileCount_[i] = currentTMXMap_->getTileSet()[i]->tileCount_;
		}

		tempText.loadFromFile("res//t2.png");

		initVertexArrays();

	}
	else
		return(false);

	return(true);
}

bool TiledMap::initVertexArrays()
{//Will initialise the vertex array with tiles to be rendered
	renderLayer_.resize(currentTMXMap_->getLayerCount());

	for (int i(0); i < renderLayer_.size(); ++i)
	{
		renderLayer_[i].setPrimitiveType(sf::Quads);
		renderLayer_[i].resize(mapBounds_.x * mapBounds_.y * 4);

		initVertArray(i);
	}

	return(true);
}

bool TiledMap::initVertArray(int index)
{

	for (int y(0); y < mapBounds_.x; ++y)
	{
		for (int x(0); x < mapBounds_.x; ++x)
		{
			sf::Vertex* tile = &renderLayer_[index][((y + x * mapBounds_.x) * 4)];

			tile[0].position = sf::Vector2f(x * tileSize_.x, y * tileSize_.y);
			tile[1].position = sf::Vector2f((x + 1) * tileSize_.x, y * tileSize_.y);
			tile[2].position = sf::Vector2f((x + 1) * tileSize_.x, (y + 1) * tileSize_.y);
			tile[3].position = sf::Vector2f(x * tileSize_.x, (y + 1) * tileSize_.y);

			int tilesetID = getTilesetID(currentTMXMap_->getLayer()[index]->data[y][x]);

			if (tilesetID == -1) //Means no tilesets matched with the tile read in
				return(false);


			int tileID = currentTMXMap_->getLayer()[index]->data[y][x] - currentTMXMap_->getTileSet()[tilesetID]->firstgid_;

			tile[0].texCoords = sf::Vector2f(tileID * tileSize_.x, 0);
			tile[1].texCoords = sf::Vector2f((tileID + 1) * tileSize_.x, 0);
			tile[2].texCoords = sf::Vector2f((tileID + 1) * tileSize_.x, tileSize_.y);
			tile[3].texCoords = sf::Vector2f(tileID * tileSize_.x, tileSize_.y);

		}
	}
	return (true);
}

void TiledMap::draw(sf::RenderTarget& renderTarget, sf::RenderStates renderStates) const
{
	renderStates.transform *= getTransform();
	renderStates.texture = &tempText;


	for (int i(0); i < renderLayer_.size(); ++i)
	{
		//Render each map layer
		renderTarget.draw(renderLayer_[i], renderStates);
	}
}

int TiledMap::getTilesetID(int tileID) const
{
	for (int i(0); i < firstGID_.size(); ++i)
	{
		if (tileID >= firstGID_[i] && tileID < (firstGID_[i] + tileCount_[i]))
			return(i);
	}
	return(-1);
}

void TiledMap::setTMXFile(Map* m)
{
	assert(m != nullptr);
	currentTMXMap_ = m;
}

bool TiledMap::isPlaceFree(const sf::FloatRect& collider) const
{
	/*  
	sf::Vector2i pos(static_cast<int>(location.x), static_cast<int> (location.y));
	bool found(false);
	int counter(0);
	int tilesetID(-1);
	int tileID(-1);
	while (counter < currentTMXMap_->getLayer().size() && !found)
	{
		if (getTilesetID(currentTMXMap_->getLayer()[counter]->data[pos.y][pos.x]) != -1)
		{
			found = true;
			tilesetID = getTilesetID(currentTMXMap_->getLayer()[counter]->data[pos.y][pos.x]);
			tileID = currentTMXMap_->getLayer()[counter]->data[pos.y][pos.x] - firstGID_[tilesetID];
		}
		++counter;
	}

	if (tilesetID != -1 && tileID != -1)
	{
		if (currentTMXMap_->getTileSet()[tilesetID]->getTilePropertyName(tileID) == "blocked" &&
			currentTMXMap_->getTileSet()[tilesetID]->getTilePropertyValue(tileID) == "false")
			return(true);
	}*/ 

	int counter(0); 
	sf::FloatRect col;
	col.width = 64;
	col.height = 64;

	while (counter < currentTMXMap_->getLayer().size())
	{
		for (int i(0); i < currentTMXMap_->getLayer().data.size(); ++i)
		{
			for (int j(0); j < currentTMXMap_->getLayer().data[i].size(); ++j)
			{
				int id = currentTMXMap_->getLayer()[counter]->data[i][j]; //Get the global id of a tile
				int tilesetID = getTilesetID( id ) ; //Convert this global id into a tileset id 
				id = id - firstGID_[tilesetID]; //work out the local id of the tile in the tileset

				std::string name = currentTMXMap_->getTilesets()[tilesetID]->getTilePropertyName(id); //Using it's local ID get the properties attached to it
				if (name == "blocked" && currentTMXMap_->getTilesets[tilesetID]->getTilePropertyValue == "true") //If the property is blocked, and has a value of true
				{
					//create a collider at the tiles position
					col.left = i * col.width; 
					col.top = j * col.height; 
					
					//If the collider passed to the function intersects with a tile collider, we have a collision!
					if (col.intersects(collider))
						return(true);
				}
			}

		}
		++counter;
	}

	return(false);
}

int TiledMap::getTileWidth() const
{
	return(currentTMXMap_->getTileWidth());
}
int TiledMap::getTileHeight() const
{
	return(currentTMXMap_->getTileHeight());
}