#include "camera_follow.h"
#include <xenity.h>

CameraFollow::CameraFollow()
{
}

void CameraFollow::Start()
{
	startPosition = GetTransform()->GetPosition();
}

void CameraFollow::Update()
{
	auto transform = GetTransform();
	auto targetTransform = cameraTarget.lock()->GetTransform();

	Vector3 pos = targetTransform->GetPosition();
	pos += offset;

	Vector3 targetPos = Vector3::Lerp(transform->GetPosition(), pos, Time::GetDeltaTime() * moveSpeed);
	
	if(lockX)
		targetPos.x = startPosition.x;
	if(lockY)
		targetPos.y = startPosition.y;
	if(lockZ)
		targetPos.z = startPosition.z;

	transform->SetPosition(targetPos);
}

ReflectiveData CameraFollow::GetReflectiveData()
{
	ReflectiveData reflectedVariables;
	Reflective::AddVariable(reflectedVariables, cameraTarget, "cameraTarget", true);
	Reflective::AddVariable(reflectedVariables, offset, "offset", true);
	Reflective::AddVariable(reflectedVariables, moveSpeed, "moveSpeed", true);
	Reflective::AddVariable(reflectedVariables, lockX, "lockX", true);
	Reflective::AddVariable(reflectedVariables, lockY, "lockY", true);
	Reflective::AddVariable(reflectedVariables, lockZ, "lockZ", true);
	return reflectedVariables;
}
