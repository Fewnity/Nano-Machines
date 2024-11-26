#include "car.h"
#include <xenity.h>

#if defined(EDITOR)
#include <xenity_editor.h>
#endif

/**
* Constructor
*/
Car::Car()
{
}

/**
* Called once when the script is enabled
*/
void Car::Start()
{
}

/**
* Called every frame
*/
void Car::Update()
{
    // if(InputSystem::GetKey(KeyCode::UP))
    // {
    //     rigidBody.lock()->SetAngular(Vector3(-force, 0, 0));
    // }
    // if(InputSystem::GetKey(KeyCode::DOWN))
    // {
    //     rigidBody.lock()->SetAngular(Vector3(force, 0, 0));
    // }

    float vel = rigidBody.lock()->GetVelocity().Magnitude() / 3;
    if(vel > 1)
        vel = 1;
    if(InputSystem::GetKey(KeyCode::LEFT))
    {
        rigidBody.lock()->SetAngular(Vector3(0, -steeringForce * vel, 0));
    }
    if(InputSystem::GetKey(KeyCode::RIGHT))
    {
        rigidBody.lock()->SetAngular(Vector3(0, steeringForce * vel, 0));
    }

    // if(InputSystem::GetKey(KeyCode::LEFT))
    // {
    //     rigidBody.lock()->SetAngular(Vector3(0, 0, -force));
    // }
    // if(InputSystem::GetKey(KeyCode::RIGHT))
    // {
    //     rigidBody.lock()->SetAngular(Vector3(0, 0, force));
    // }
    if(InputSystem::GetKey(KeyCode::UP))
    {
        rigidBody.lock()->SetAngular(carGO.lock()->GetTransform()->GetLeft() * -force);
    }
    if(InputSystem::GetKey(KeyCode::DOWN))
    {
        rigidBody.lock()->SetAngular(carGO.lock()->GetTransform()->GetLeft() * force);
    }

    // if(InputSystem::GetKey(KeyCode::LEFT))
    // {
    //     rigidBody.lock()->SetAngular(GetTransform()->GetLeft() * force);
    // }
    //  if(InputSystem::GetKey(KeyCode::RIGHT))
    // {
    //     rigidBody.lock()->SetAngular(GetTransform()->GetLeft() * -force);
    // }

    carGO.lock()->GetTransform()->SetRotation(Vector3(0, carGO.lock()->GetTransform()->GetEulerAngles().y, 0));
}

void Car::OnDrawGizmos()
{
// #if defined(EDITOR)
// Color lineColor = Color::CreateFromRGBAFloat(0, 1, 0, 1);

// Gizmo::SetColor(lineColor);

// Gizmo::DrawLine(GetTransform()->GetPosition(), GetTransform()->GetPosition() + GetTransform()->GetForward() * 3);
// #endif
}

/**
* Lists all variables to show in inspector
*/
ReflectiveData Car::GetReflectiveData()
{
    ReflectiveData reflectedVariables;
    Reflective::AddVariable(reflectedVariables, rigidBody, "rigidBody", true); // true = isVisibleInInspector
    Reflective::AddVariable(reflectedVariables, force, "force", true);
    Reflective::AddVariable(reflectedVariables, steeringForce, "steeringForce", true);
    Reflective::AddVariable(reflectedVariables, carGO, "carGO", true);
    return reflectedVariables;
}
