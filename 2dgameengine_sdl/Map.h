#ifndef MAP_H
#define MAP_H

#include <string>

extern EntityManager manager;

class Map {
private:
	std::string textureId;
	int scale;
	int tileSize;

public:
	Map(std::string textureId, int scale, int tileSize);
	~Map();

	// Load the whole map by reading the source txt file
	void LoadMap(std::string filePath, int mapSizeX, int mapSizeY);

	// Add a tile to the map
	void AddTile(int sourceX, int sourceY, int x, int y);
};

#endif