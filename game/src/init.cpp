#include "internal/entity.h"
#include "component.h"
#include <iostream>


struct PhysicsComponent : public Component<PhysicsComponent> {
    PhysicsComponent() : Component() {}
    int i;
};

struct HitboxComponent : Component<HitboxComponent> {
    HitboxComponent() : Component() {}
    int i;
};

struct HealthComponent : Component<HealthComponent> {
    HealthComponent() : Component() {}
    int i;
};

int main() {
    std::cout << "finished component registry" << std::endl;
}