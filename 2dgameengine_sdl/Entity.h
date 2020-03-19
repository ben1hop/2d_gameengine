#ifndef ENTITY_H
#define ENTITY_H

#include <vector>
#include <string>
#include <map>
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
	// Constructors
	Entity(EntityManager& manager);
	Entity(EntityManager& manager, std::string name);


	void Update(float deltaTime);
	void Render();
	void Destroy();
	bool isActivee() const;


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

	template <typename T>
	T* GetComponent() {
		return static_cast<T*>(componentTypeMap[&typeid(T)]);
	}
};

#endif