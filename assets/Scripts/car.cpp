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
    float vel = rigidBody.lock()->GetVelocity().Magnitude() / 3;
    if(vel > 1)
        vel = 1;

    if(yTorque > 0.1)
    {
        yTorque -= Time::GetDeltaTime() * 3;
        if(yTorque < 0.1)
        {
            yTorque = 0;
        }
    }
    else if(yTorque < -0.1)
    {
        yTorque += Time::GetDeltaTime() * 3;
        if(yTorque > 0.1)
        {
            yTorque = 0;
        }
    }
    else
        yTorque = 0;


    bool hasTurned = false;
    if(InputSystem::GetKey(KeyCode::LEFT) && playerIndex == 0)
    {
        yTorqueAdd += Time::GetDeltaTime() * yTorqueAddSpeed;
        if(yTorqueAdd > steeringForce)
            yTorqueAdd = steeringForce;
        yTorque = -yTorqueAdd * vel;
        hasTurned = true;
        // rigidBody.lock()->ApplyTorque(Vector3(0, -steeringForce * vel, 0));
    }
    if(InputSystem::GetKey(KeyCode::RIGHT) && playerIndex == 0)
    {
        yTorqueAdd += Time::GetDeltaTime() * yTorqueAddSpeed;
        if(yTorqueAdd > steeringForce)
            yTorqueAdd = steeringForce;
        yTorque = yTorqueAdd * vel;
        hasTurned = true;
        // rigidBody.lock()->ApplyTorque(Vector3(0, steeringForce * vel, 0));
    }
    if(!hasTurned)
    {
         yTorqueAdd = 0;
    // if(yTorqueAdd > 0.1)
    // {
    //     yTorqueAdd -= Time::GetDeltaTime() * 3;
    //     if(yTorqueAdd < 0.1)
    //     {
    //         yTorqueAdd = 0;
    //     }
    // }
    // // else if(yTorqueAdd < -0.1)
    // // {
    // //     yTorqueAdd += Time::GetDeltaTime() * 3;
    // //     if(yTorqueAdd > 0.1)
    // //     {
    // //         yTorqueAdd = 0;
    // //     }
    // // }
    // else
    //     yTorqueAdd = 0;
    }

    Vector3 angularVelocity = rigidBody.lock()->GetAngularVelocity();
    Vector3 leftDir = carGO.lock()->GetTransform()->GetLeft();
    Vector3 fwd = carGO.lock()->GetTransform()->GetForward();
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

    if(InputSystem::GetKey(KeyCode::UP) && playerIndex == 0)
    {
        rigidBody.lock()->ApplyTorque(carGO.lock()->GetTransform()->GetLeft() * -force);
    }
    if(InputSystem::GetKey(KeyCode::DOWN) && playerIndex == 0)
    {
        rigidBody.lock()->ApplyTorque(carGO.lock()->GetTransform()->GetLeft() * force);
    }

    Vector3 moveDir;
    if (moveDir.x == 0 && moveDir.z == 0)
    {
        moveDir.x = InputSystem::GetLeftJoystick(playerIndex).x;
        if(realSpeed < 0)
        {    
            moveDir.x = -moveDir.x;
        }
        // moveDir.z = InputSystem::leftJoystick.y;
    }
    if(InputSystem::GetKey(KeyCode::CROSS, playerIndex))
    {
        moveDir.z = -1;
    }
    if(InputSystem::GetKey(KeyCode::SQUARE, playerIndex))
    {
        moveDir.z = 1;
    }
    rigidBody.lock()->ApplyTorque(carGO.lock()->GetTransform()->GetLeft() * moveDir.z * force);
    yTorque =  moveDir.x * steeringForce * realSteeringSpeed;

    Vector3 t = rigidBody.lock()->GetAngularVelocity();
    t.y = 0;

    // Reduce side speed
    float projectionFactor = fwd.Dot(t) / fwd.MagnitudeSquared();
    Vector3 projection = fwd * projectionFactor;
    Vector3 perpendicular = t - projection;
    perpendicular.y = yTorque;
    rigidBody.lock()->SetAngularVelocity(perpendicular);

    if(InputSystem::GetKeyDown(KeyCode::RTRIGGER1, playerIndex))
    {
        Vector3 currentVel = rigidBody.lock()->GetVelocity();
        currentVel.y += jumpForce;
        rigidBody.lock()->SetVelocity(currentVel);
    }
    // Vector3 fwd = carGO.lock()->GetTransform()->GetLeft();
    // fwd.x = -fwd.x;
    // fwd.y = 1;
    // rigidBody.lock()->SetAngularFactor(fwd);

    // Debug::Print(rigidBody.lock()->GetTorque().ToString());
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
#if defined(EDITOR)
    // Color lineColor = Color::CreateFromRGBAFloat(0, 1, 0, 1);

    // Gizmo::SetColor(lineColor);
    // Vector3 t2 = rigidBody.lock()->GetAngularVelocity();
    // Gizmo::DrawLine(GetTransform()->GetPosition(), GetTransform()->GetPosition() + t2 * 3);
    // Debug::Print((t2 * carGO.lock()->GetTransform()->GetLeft()).ToString());
    // Debug::Print(std::sin())
    // float realSpeed = t2.x * carGO.lock()->GetTransform()->GetLeft().x + t2.z * carGO.lock()->GetTransform()->GetLeft().z;
    // Debug::Print(std::to_string(realSpeed));
    // Gizmo::DrawLine(GetTransform()->GetPosition(), GetTransform()->GetPosition() + carGO.lock()->GetTransform()->GetForward() * 3);

    // Color velocityDirlineColor = Color::CreateFromRGBAFloat(1, 1, 0, 1);

    // Gizmo::SetColor(velocityDirlineColor);
    
    // Vector3 t = rigidBody.lock()->GetAngularVelocity();
    // t.y = 0;
    // Gizmo::DrawLine(GetTransform()->GetPosition(), GetTransform()->GetPosition() + t * 3);

    // Vector3 fwd = carGO.lock()->GetTransform()->GetForward();
    // // Vector3 t2 = rigidBody.lock()->GetAngularVelocity();
    // float projectionFactor = fwd.Dot(t) / fwd.MagnitudeSquared();
    // Vector3 projection = fwd * projectionFactor;

    // // Calcul du vecteur perpendiculaire
    // Vector3 perpendicular = t - projection;

    // Color velocityDirlineColor2 = Color::CreateFromRGBAFloat(1, 1, 1, 1);

    // Gizmo::SetColor(velocityDirlineColor2);
    // Gizmo::DrawLine(GetTransform()->GetPosition(), GetTransform()->GetPosition() + perpendicular * 3);
#endif
}

/**
* Lists all variables to show in inspector
*/
ReflectiveData Car::GetReflectiveData()
{
    BEGIN_REFLECTION();
    ADD_VARIABLE(playerIndex, true);
    ADD_VARIABLE(rigidBody, true);
    ADD_VARIABLE(force, true);
    ADD_VARIABLE(steeringForce, true);
    ADD_VARIABLE(carGO, true);
    ADD_VARIABLE(yTorqueAdd, true);
    ADD_VARIABLE(yTorqueAddSpeed, true);
    ADD_VARIABLE(jumpForce, true);
    END_REFLECTION();
}
