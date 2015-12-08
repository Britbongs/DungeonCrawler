#include "TiledMap.h"

TiledMap::TiledMap(Map* tmxMap)
	: currentTMXMap_(tmxMap)
{
}

TiledMap::~TiledMap()
{
}

bool TiledMap::initaliseMap()
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

	for (int i(0); i < mapBounds_.x; ++i)
	{
		for (int j(0); j < mapBounds_.y; ++j)
		{
			sf::Vertex* tile = &renderLayer_[index][(i*j * 4)];

			tile[0].position = sf::Vector2f(i * tileSize_.x, j * tileSize_.y);
			tile[1].position = sf::Vector2f((i + 1) * tileSize_.x, j * tileSize_.y);
			tile[2].position = sf::Vector2f((i + 1) * tileSize_.x, (j + 1) * tileSize_.y);
			tile[3].position = sf::Vector2f(i * tileSize_.x, (j + 1) * tileSize_.y);

			//int tileID = data[i][j];
			int tilesetID = getTilesetID(currentTMXMap_->getLayer()[index]->data[i][j]);

			if (tilesetID == -1) //Means no tilesets matched with the tile read in
				return(false);

			int tileID = currentTMXMap_->getLayer()[index]->data[i][j] - tilesetID;

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
	{//Render each map layer
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