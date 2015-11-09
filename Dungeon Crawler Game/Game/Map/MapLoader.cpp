#include "MapLoader.h"

MapLoader::MapLoader(std::string FILENAME) : FILENAME(FILENAME)
{
}


MapLoader::~MapLoader()
{
	
	for (size_t i(0); i < mapBounds_.x; ++i)
	{
		delete[] textureMap_[i];
		delete[] blockedMap_[i];
	}
	delete[] textureMap_;
	delete[] blockedMap_;
}

bool MapLoader::loadMap()
{
	fileLoader_.open(FILENAME, std::ios::in);
	playerStart_.x = 0; 
	playerStart_.y = 0;

	if (fileLoader_.fail())
	{
		std::cout << "Failed to open map file." << std::endl;
		fileLoader_.close();
		return(false);
	}
	else
	{
		fileLoader_ >> mapBounds_.x;
		fileLoader_ >> mapBounds_.y;
		fileLoader_ >> tileSize_; 
		fileLoader_ >> scaleFactor_;
		{//Creating map arrays
			assert(mapBounds_.x > 0 && mapBounds_.y > 0);//check that the map file has the correct data in it
			textureMap_ = new int*[mapBounds_.x];
			blockedMap_ = new char*[mapBounds_.x];
											
			for (int i = 0; i < mapBounds_.x; ++i)
			{
				textureMap_[i] = new int[mapBounds_.y];
				blockedMap_[i] = new char[mapBounds_.y];
			}

			for (size_t i (0); i < mapBounds_.x; ++i)
				for (size_t j(0); j < mapBounds_.y; ++j)
					fileLoader_ >> textureMap_[i][j];
			for (size_t i(0); i < mapBounds_.x; ++i)
				for (size_t j(0); j < mapBounds_.y; ++j)
					fileLoader_ >> blockedMap_[i][j];

			fileLoader_ >> playerStart_.x; 
			fileLoader_ >> playerStart_.y;
		}
		printMap();
	}
	fileLoader_.close();
	return(true);
}

void MapLoader::printMap() const
{
	assert(blockedMap_ != nullptr && textureMap_ != nullptr && mapBounds_ .x > 0 && mapBounds_.y > 0);
	for (size_t i (0); i < mapBounds_.x; ++i)
	{
		for (size_t j(0); j < mapBounds_.y; ++j)
			std::cout << textureMap_[i][j] << " ";
		std::cout << std::endl;
	}

	std::cout << std::endl;

	for (size_t i(0); i < mapBounds_.x; ++i)
	{
		for (size_t j(0); j < mapBounds_.y; ++j)
			std::cout << blockedMap_[i][j] << " ";
		std::cout << std::endl;
	}


}

int** MapLoader::getTextureMap() const
{
	assert(textureMap_ != nullptr);
	return(textureMap_);
}

char** MapLoader::getBlockedMap() const
{
	assert(blockedMap_ != nullptr);
	return(blockedMap_);
}

sf::Vector2u MapLoader::getMapBounds() const
{
	return(mapBounds_);
}

sf::Vector2i MapLoader::getPlayerStart() const
{
	return(playerStart_); 
}

float MapLoader::getScaleFactor() const
{
	return(scaleFactor_);
}

int MapLoader::getTileSize() const
{
	return(tileSize_);
}