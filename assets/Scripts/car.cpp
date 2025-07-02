#include "car.h"
#include <xenity.h>

#if defined(EDITOR)
#include <xenity_editor.h>
#endif

/**
* Called every frame
*/
void Car::Update()
{
    Vector3 angularVelocity = rigidBody.lock()->GetAngularVelocity();
    Vector3 leftDir = carGO.lock()->GetTransform()->GetLeft();
    Vector3 fwd = carGO.lock()->GetTransform()->GetForward();

    // Get streering speed depending of the car speed
    float realSpeed = -(angularVelocity.x * leftDir.x + angularVelocity.z * leftDir.z);
    float realSteeringSpeed = realSpeed / 3.0f;
    if(realSteeringSpeed < 0)
    {
        realSteeringSpeed = -realSteeringSpeed;
    }
    if(realSteeringSpeed > 1)
    {  
        realSteeringSpeed = 1;
    }

    // Get player movement inputs
    Vector3 moveDir;
    if(InputSystem::GetKey(KeyCode::LEFT))
    {
        moveDir.x = -1;
    }
    else if(InputSystem::GetKey(KeyCode::RIGHT))
    {
        moveDir.x = 1;
    }

    if (moveDir.x == 0 && moveDir.z == 0)
    {
        moveDir.x = InputSystem::GetLeftJoystick(playerIndex).x;
    }
    
    // If the car is reversing, reverse the side direction
    if(realSpeed < 0)
    {    
        moveDir.x = -moveDir.x;
    }
    
    if(InputSystem::GetKey(KeyCode::CROSS, playerIndex) || InputSystem::GetKey(KeyCode::UP))
    {
        moveDir.z = -1;
    }
    else if(InputSystem::GetKey(KeyCode::SQUARE, playerIndex) || InputSystem::GetKey(KeyCode::DOWN))
    {
        moveDir.z = 1;
    }

    if(InputSystem::GetLeftTrigger() >= 0.1f)
    {
        moveDir.z = InputSystem::GetLeftTrigger();
    }
    if(InputSystem::GetRightTrigger() >= 0.1f)
    {
        moveDir.z = -InputSystem::GetRightTrigger();
    }

    // Apply movements
    rigidBody.lock()->ApplyTorque(carGO.lock()->GetTransform()->GetLeft() * moveDir.z * force);
    
    // Reduce side speed
    Vector3 angularVelocityNoY = rigidBody.lock()->GetAngularVelocity();
    angularVelocityNoY.y = 0;
    float projectionFactor = fwd.Dot(angularVelocityNoY) / fwd.SquaredMagnitude();
    Vector3 projection = fwd * projectionFactor;
    Vector3 perpendicular = angularVelocityNoY - projection;
    float yTorque = moveDir.x * steeringForce * realSteeringSpeed;
    perpendicular.y = yTorque;
    rigidBody.lock()->SetAngularVelocity(perpendicular);

    // Check if the player wants to jump
    if(InputSystem::GetKeyDown(KeyCode::RTRIGGER1, playerIndex) ||
     InputSystem::GetKeyDown(KeyCode::SPACE) ||
      InputSystem::GetKeyDown(KeyCode::TRIANGLE, playerIndex))
    {
        Vector3 currentVel = rigidBody.lock()->GetVelocity();
        currentVel.y += jumpForce;
        rigidBody.lock()->SetVelocity(currentVel);
    }

    particleSystem.lock()->SetSpawnRate(realSpeed);

    // Reset X and Z angles
    carGO.lock()->GetTransform()->SetEulerAngles(Vector3(0, carGO.lock()->GetTransform()->GetEulerAngles().y, 0));
}

/**
* Lists all variables to show in inspector
*/
ReflectiveData Car::GetReflectiveData()
{
    BEGIN_REFLECTION();
    ADD_VARIABLE(playerIndex, true);
    ADD_VARIABLE(rigidBody, true);
    ADD_VARIABLE(particleSystem, true);
    ADD_VARIABLE(force, true);
    ADD_VARIABLE(steeringForce, true);
    ADD_VARIABLE(carGO, true);
    ADD_VARIABLE(jumpForce, true);
    END_REFLECTION();
}
