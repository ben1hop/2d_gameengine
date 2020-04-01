#include "./EntityManager.h"
#include "./Collision.h"
#include "./ColliderComponent.h"

#include <iostream>

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

void EntityManager::ListAllEntites() const {
	unsigned int i = 0;
	for (auto& entity : entities) {
		std::cout << "Entity[" << i << "]: " << entity->name << std::endl;
		entity->ListAllComponents();
		i++;
	}
}

CollisionType EntityManager::CheckCollision() const {
	// This one needs a little bit of editing
	// Too much itterations , doesnt check opposite order pairs
	for (auto& thisEntity : entities) {
		if (thisEntity->HasComponent<ColliderComponent>()) {
			ColliderComponent* thisCollider = thisEntity->GetComponent<ColliderComponent>();
			for (auto& thatEntity : entities) {
				if (thisEntity->name.compare(thatEntity->name) != 0 && thatEntity->HasComponent<ColliderComponent>()) {
					ColliderComponent* thatCollider = thatEntity->GetComponent<ColliderComponent>();
					if (Collision::CheckRectangleCollision(thisCollider->collider, thatCollider->collider)) {
						if (
							thisCollider->colliderTag.compare("PLAYER") == 0 &&
							thatCollider->colliderTag.compare("ENEMY") == 0
							) {
							return PLAYER_ENEMY_COLLISION;
						}
						if (
							thisCollider->colliderTag.compare("PLAYER") == 0 &&
							thatCollider->colliderTag.compare("PROJECTILE") == 0
							) {
							return PLAYER_PROJECTILE_COLLISION;
						}
						if (
							thisCollider->colliderTag.compare("ENEMY") == 0 &&
							thatCollider->colliderTag.compare("FRIENDLY_PROJECTILE") == 0
							) {
							return ENEMY_PROJECTILE_COLLISION;
						}
						if (
							thisCollider->colliderTag.compare("PLAYER") == 0 &&
							thatCollider->colliderTag.compare("LEVEL_COMPLETE") == 0
							) {
							return PLAYER_LEVEL_COMPLETE_COLLISION;
						}
					}
				}
			}
		}
	}
}