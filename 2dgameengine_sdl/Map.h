#ifndef MAP_H
#define MAP_H

#include <string>

class Map {
private:
	std::string textureId;
	int scale;
	int tileSize;

public:
	Map(std::string textureId, int scale, int tileSize) {
		this->textureId = textureId;
		this->scale = scale;
		this->tileSize = tileSize;
	}
	~Map();
	void LoadMap(std::string filePath, int mapSizeX, int mapSizeY) {
		// TODO read the map
	}
	void AddTile(int sourceX, int sourceY, int x, int y) {
		// TODO
	}
};

#endif