#pragma once

#include <engine/component.h>

class RigidBody;

class Car : public Component
{
public:
    Car();

    void Start() override;
    void Update() override;

    ReflectiveData GetReflectiveData() override;
    float force = 1;
    float steeringForce = 1;
    void OnDrawGizmos() override;
    
private:
    std::weak_ptr<GameObject> carGO;
    std::weak_ptr<RigidBody> rigidBody;
    float yTorque = 0;
    float yTorqueAdd = 0;
    float yTorqueAddSpeed = 0;
    float jumpForce = 1;
    int playerIndex = 0;
};
