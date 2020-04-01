#ifndef ENTITYMANAGER_H
#define ENTITYMANAGER_H

#include "./Entity.h"
#include "./Component.h"
#include <vector>

class EntityManager
{
private:
	std::vector<Entity*> entities;
public:
	void ClearData();
	void Update(float deltaTime);
	void Render();
	bool HasNoEntities() const;

	
	std::vector<Entity*> GetEntitites() const;
	std::vector<Entity*> GetEntititesByLayer(LayerType layer) const;
 	unsigned int GetEntityCount() const;
	void ListAllEntites() const;

	Entity& AddEntity(std::string entityName, LayerType layer);

	CollisionType CheckCollision() const;
};

#endif
