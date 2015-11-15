#include "Map.h"


Map::Map(int** textureMap, char** blockedMap, sf::Vector2u mapBounds, int tileSize, sf::Texture tiles, float scaleFactor) : TILES(tiles), TILESIZE(tileSize), MAP_BOUNDS(mapBounds), TEXTURE_TILESIZE((float)tileSize / scaleFactor)
{

	std::cout << tileSize << std::endl;
	std::cout << mapBounds.x << " : " << mapBounds.y << std::endl;
	initVertexArray(textureMap);
	Map::blockedMap_ = new char*[mapBounds.x];
	for (int i(0); i < mapBounds.x; ++i)
		Map::blockedMap_[i] = new char[mapBounds.y];

	for (int i(0); i < mapBounds.x; ++i)
	{
		for (int j(0); j < mapBounds.y; ++j)
		{
			Map::blockedMap_[i][j] = blockedMap[i][j];
		}
	}
	srand(static_cast<unsigned int> (time(0)));
}

Map::~Map()
{
	for (int i = 0; i < MAP_BOUNDS.x; ++i)
		delete[] blockedMap_[i];

	delete[] blockedMap_;
}

void Map::initVertexArray(int** textureMap)
{
	assert(MAP_BOUNDS.x > 0 && MAP_BOUNDS.y > 0);

	mapVertexArray_.setPrimitiveType(sf::Quads);
	mapVertexArray_.resize(MAP_BOUNDS.x * MAP_BOUNDS.y * 4);

	for (int i(0); i < MAP_BOUNDS.x; ++i)
	{
		for (int j(0); j < MAP_BOUNDS.y; ++j)
		{
			sf::Vertex* tile = &mapVertexArray_[(i + j*MAP_BOUNDS.x) * 4];

			tile[0].position = sf::Vector2f(i * TILESIZE, j * TILESIZE);
			tile[1].position = sf::Vector2f((i + 1)* TILESIZE, j * TILESIZE);
			tile[2].position = sf::Vector2f((i + 1) * TILESIZE, (j + 1) * TILESIZE);
			tile[3].position = sf::Vector2f(i * TILESIZE, (j + 1) * TILESIZE);

			int tileID = textureMap[i][j];

			tile[0].texCoords = sf::Vector2f(tileID * TEXTURE_TILESIZE, 0);
			tile[1].texCoords = sf::Vector2f((tileID + 1)* TEXTURE_TILESIZE, 0);
			tile[2].texCoords = sf::Vector2f((tileID + 1)* TEXTURE_TILESIZE, TEXTURE_TILESIZE);
			tile[3].texCoords = sf::Vector2f(tileID * TEXTURE_TILESIZE, TEXTURE_TILESIZE);


		}
	}

}

void Map::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	states.texture = &TILES;

	target.draw(mapVertexArray_, states);
}

bool Map::isPlaceFree(sf::FloatRect collider)
{
	for (int i(0); i < MAP_BOUNDS.x; ++i)
	{
		for (int j(0); j < MAP_BOUNDS.y; ++j)
		{
			if (sf::FloatRect(i * TILESIZE, j * TILESIZE, TILESIZE, TILESIZE).intersects(collider) && blockedMap_[i][j] == BLOCKED)
			{
				return(false);
			}
		}
	}
	return(true);
}

bool Map::isContained(sf::FloatRect collider)
{
	for (int i(0); i < MAP_BOUNDS.x; ++i)
	{
		for (int j(0); j < MAP_BOUNDS.y; ++j)
		{
			sf::FloatRect tile(i * TILESIZE, j * TILESIZE, TILESIZE, TILESIZE);
			if (tile.intersects(collider) &&
				blockedMap_[i][j] == BLOCKED)
			{
				return(true);
			}
		}
	}
	return(false);
}

bool Map::isPointContained(sf::Vector2f point) const
{

	for (int i(0); i < MAP_BOUNDS.x; ++i)
	{
		for (int j(0); j < MAP_BOUNDS.y; ++j)
		{
			if (blockedMap_[i][j] == BLOCKED && sf::FloatRect(i*TILESIZE, j*TILESIZE, TILESIZE, TILESIZE).contains(point))
				return(true);
		}
	}
	return(false);
}

sf::Vector2u Map::getMapBounds() const
{
	return(MAP_BOUNDS);
}

sf::Vector2i Map::randomFreeTile() const
{
	sf::Vector2i freeLoc((rand() % MAP_BOUNDS.x) + 1, (rand() % MAP_BOUNDS.y) + 1);

	while (blockedMap_[freeLoc.x][freeLoc.y] == BLOCKED)
	{
		freeLoc.x = (rand() % MAP_BOUNDS.x) + 1;
		freeLoc.y = (rand() % MAP_BOUNDS.y) + 1;
	}
	return(freeLoc);
}