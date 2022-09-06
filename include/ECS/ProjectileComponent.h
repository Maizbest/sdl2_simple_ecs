#ifndef B808ECC4_E557_4D05_B5AD_A389DCCDF765
#define B808ECC4_E557_4D05_B5AD_A389DCCDF765

#include "ECS/Components.h"
#include "ECS/ESC.h"

class ProjectileComponent : public Component {
 public:
  ProjectileComponent(int range, int speed, Vector2d velocity)
      : m_range(range),
        m_speed(speed),
        m_velocity(velocity){

        };
  ~ProjectileComponent(){};

  void init() override {
    transform = &entity->getComponent<TransformComponent>();
    transform->velocity = m_velocity;
  }
  void update() override {
    m_distance += m_speed;

    if (m_distance > m_range ||
        transform->position.x > Game::camera.x + Game::camera.w ||
        transform->position.x < Game::camera.x ||
        transform->position.y > Game::camera.y + Game::camera.h ||
        transform->position.y < Game::camera.y) {
      std::cout << "Projectile out of bounds" << std::endl;
      entity->destroy();
    }
  }
  void draw() override {}

 private:
  TransformComponent* transform;

  int m_range = 0;
  int m_speed = 0;
  int m_distance = 0;
  Vector2d m_velocity;
};

#endif /* B808ECC4_E557_4D05_B5AD_A389DCCDF765 */
