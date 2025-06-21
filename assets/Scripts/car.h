#pragma once

#include <engine/component.h>

class RigidBody;
class ParticleSystem;

class Car : public Component
{
public:
    float force = 1;
    float steeringForce = 1;
    
private:
    void Update() override;
    ReflectiveData GetReflectiveData() override;

    std::weak_ptr<GameObject> carGO;
    std::weak_ptr<ParticleSystem> particleSystem;
    std::weak_ptr<RigidBody> rigidBody;
    float jumpForce = 1;
    int playerIndex = 0;
};
