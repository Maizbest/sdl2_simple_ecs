#ifndef B83937A4_4DBE_4438_89E7_9FAD13C19DAB
#define B83937A4_4DBE_4438_89E7_9FAD13C19DAB

#include <algorithm>
#include <array>
#include <bitset>
#include <iostream>
#include <memory>
#include <vector>

class Component;
class Entity;

using ComponentID = std::size_t;

inline ComponentID getComponentTypeID() {
  static ComponentID lastID = 0;
  return lastID++;
}

template <typename T>
inline ComponentID getComponentTypeID() noexcept {
  static ComponentID typeID = getComponentTypeID();
  return typeID;
}

constexpr std::size_t maxComponents = 32;

using ComponentBitSet = std::bitset<maxComponents>;
using ComponentArray = std::array<Component*, maxComponents>;

class Component {
 public:
  Entity* entity;

  virtual void init() = 0;
  virtual void update() = 0;
  virtual void draw() = 0;

  virtual ~Component() {};
};

class Entity {
 private:
  bool active = true;
  std::vector<std::unique_ptr<Component>> components;

  ComponentArray componentArray;
  ComponentBitSet componentBitset;

 public:
  void update() {
    for (auto& component : components) component->update();
  }

  void draw() {
    for (auto& component : components) component->draw();
  }

  bool isActive() const { return active; }
  void destroy() { active = false; }

  template <typename T>
  bool hasComponents() const {
    return componentBitset[getComponentTypeID<T>()];
  }

  template <typename T, typename... TArgs>
  T& addComponent(TArgs&&... args) {
    T* newComponent = new T(std::forward<TArgs>(args)...);
    static_assert(std::is_base_of<Component, T>::value,
                  "type parameter for addComponent<T>() function must derive "
                  "from Component");
    newComponent->entity = this;

    std::unique_ptr<Component> uPtr(newComponent);
    components.emplace_back(std::move(uPtr));

    componentArray[getComponentTypeID<T>()] = newComponent;
    componentBitset[getComponentTypeID<T>()] = true;

    newComponent->init();
    return *newComponent;
  }

  template <typename T>
  T& getComponent() const {
    static_assert(std::is_base_of<Component, T>::value,
                  "type parameter for getComponent<T>() function must derive "
                  "from Component");
    auto ptr(componentArray[getComponentTypeID<T>()]);
    return *static_cast<T*>(ptr);
  }
};

class Manager {
 private:
  std::vector<std::unique_ptr<Entity>> entities;

 public:
  void update() {
    for (auto& entity : entities) entity->update();
  }

  void draw() {
    for (auto& entity : entities) entity->draw();
  }

  void refresh() {
    entities.erase(std::remove_if(std::begin(entities), std::end(entities),
                                  [](const std::unique_ptr<Entity>& entity) {
                                    return !entity->isActive();
                                  }),
                   std::end(entities));
  }

  Entity& addEntity() {
    Entity* entity = new Entity();
    std::unique_ptr<Entity> uPtr(entity);
    entities.emplace_back(std::move(uPtr));
    return *entity;
  }
};

#endif /* B83937A4_4DBE_4438_89E7_9FAD13C19DAB */
