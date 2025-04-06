#include "camera_follow.h"
#include <xenity.h>

CameraFollow::CameraFollow()
{
}

void CameraFollow::Start()
{
	startPosition = GetTransform()->GetPosition();
	startRotation = GetTransform()->GetRotation();
	Debug::Print(startRotation.ToString());

}

void CameraFollow::Update()
{
	auto transform = GetTransform();
	auto targetTransform = cameraTarget.lock()->GetTransform();

	Vector3 pos = targetTransform->GetPosition();
	//pos += offset;

	if(!rearMode)
	{
		Vector3 targetPos = Vector3::Lerp(transform->GetPosition(), pos, Time::GetDeltaTime() * moveSpeed);
		
		if(lockX)
			targetPos.x = startPosition.x;
		if(lockY)
			targetPos.y = startPosition.y;
		if(lockZ)
			targetPos.z = startPosition.z;
	
		transform->SetPosition(targetPos);
	}
	else
	{
		pos += targetTransform->GetBackward() * zDistanceMultiplier;
		pos += targetTransform->GetUp() * yDistanceMultiplier;
		Vector3 targetPos = Vector3::Lerp(transform->GetPosition(), pos, Time::GetDeltaTime() * moveSpeed);
		transform->SetPosition(targetPos);
		transform->SetRotation(Quaternion::Lerp(transform->GetRotation(), targetTransform->GetRotation() * startRotation, Time::GetDeltaTime() * rotationSpeed));
	}
}

ReflectiveData CameraFollow::GetReflectiveData()
{
	BEGIN_REFLECTION();
	ADD_VARIABLE(cameraTarget, true);
	ADD_VARIABLE(offset, true);
	ADD_VARIABLE(yDistanceMultiplier, true);
	ADD_VARIABLE(zDistanceMultiplier, true);
	ADD_VARIABLE(moveSpeed, true);
	ADD_VARIABLE(rotationSpeed, true);
	ADD_VARIABLE(lockX, true);
	ADD_VARIABLE(lockY, true);
	ADD_VARIABLE(lockZ, true);
	ADD_VARIABLE(rearMode, true);
	END_REFLECTION();
}
