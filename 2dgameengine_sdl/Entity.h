#ifndef ENTITY_H
#define ENTITY_H

#include <vector>
#include <string>
#include <map>
#include "./Constans.h"
#include "./EntityManager.h"
#include "./Component.h"

class Component;
class EntityManager;

class Entity
{
private:
	EntityManager& manager;
	bool isActive;

	// Storing every instance of an added component
	std::vector<Component*> components;
	std::map<const type_info*, Component*> componentTypeMap;

public:
	// Entitys name
	std::string name;
	LayerType layer;
	// Constructors
	Entity(EntityManager& manager);
	Entity(EntityManager& manager, std::string name, LayerType layer);


	void Update(float deltaTime);
	void Render();
	void Destroy();
	bool IsActive() const;
	void ListAllComponents() const {}; //TODO


	// AddComponent T is for any component type
	template<typename T, typename... TArgs>
	T& AddComponent(TArgs&&... args) {
		T* newComponent(new T(std::forward<TArgs>(args)...));

		componentTypeMap[&typeid(*newComponent)] = newComponent;

		newComponent->owner = this;
		components.emplace_back(newComponent);
		newComponent->Initialize();

		return *newComponent;
	}

	// return if you have this kind of type
	template <typename T>
	bool HasComponent() const {
		return componentTypeMap.count(&typeid(T));
	}

	template <typename T>
	T* GetComponent() {
		return static_cast<T*>(componentTypeMap[&typeid(T)]);
	}
};

#endif