#ifndef ASSETMANAGER_H
#define ASSETMANAGER_H

#include <map>
#include <string>
#include "./TextureManager.h"
#include "./EntityManager.h"

// Storing an entities textures
class AssetManager {
private:
	EntityManager* manager;
	std::map<std::string, SDL_Texture*> textures;
public:
	AssetManager(EntityManager* manager);
	~AssetManager();
	void ClearData();
	void AddTexture(std::string texureId, const char* filePath);
	SDL_Texture* GetTexture(std::string textureId);
};

#endif

