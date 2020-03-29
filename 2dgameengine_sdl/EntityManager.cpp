#include "./EntityManager.h"

void EntityManager::ClearData() {
	for (auto& entity : entities) {
		entity->Destroy();
	}
}

bool EntityManager::HasNoEntities() const {
	return entities.size() == 0;
}

void EntityManager::Update(float deltaTime) {
	for (auto& entity : entities) {
		entity->Update(deltaTime);
	}
}

std::vector<Entity*> EntityManager::GetEntititesByLayer(LayerType layer) const {
	std::vector<Entity*> selectEntities;
	for (auto& entity : entities) {
		if (entity->layer == layer) {
			selectEntities.emplace_back(entity);
		}
	}
	return selectEntities;
}

void EntityManager::Render() {

	for (int layerNumber = 0; layerNumber < NUM_LAYERS ; layerNumber++) {
		for (auto& entity : GetEntititesByLayer(static_cast<LayerType>(layerNumber))) {
			entity->Render();
		}
	}
}

Entity& EntityManager::AddEntity(std::string entityName , LayerType layer) {
	Entity* entity = new Entity(*this, entityName, layer);
	entities.emplace_back(entity);
	return *entity;
}

std::vector<Entity*> EntityManager::GetEntitites() const {
	return entities;
}

unsigned int EntityManager::GetEntityCount() const {
	return entities.size();
}