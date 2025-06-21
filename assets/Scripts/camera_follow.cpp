#include "camera_follow.h"
#include <xenity.h>

void CameraFollow::Update()
{
	if(std::shared_ptr<GameObject> targetLock = cameraTarget.lock())
	{
		std::shared_ptr<Transform> transform = GetTransform();
		std::shared_ptr<Transform> targetTransform = targetLock->GetTransform();
	
		Vector3 targetPos = targetTransform->GetPosition();
	
		targetPos += targetTransform->GetBackward() * zDistanceMultiplier;
		targetPos += targetTransform->GetUp() * yDistanceMultiplier;

		Vector3 newPos = Vector3::Lerp(transform->GetPosition(), targetPos, Time::GetDeltaTime() * moveSpeed);
		transform->SetPosition(newPos);
		transform->SetRotation(Quaternion::Lerp(transform->GetRotation(), targetTransform->GetRotation() * Quaternion::Euler(cameraAngle.x, cameraAngle.y, cameraAngle.z), Time::GetDeltaTime() * rotationSpeed));
	}
}

ReflectiveData CameraFollow::GetReflectiveData()
{
	BEGIN_REFLECTION();
	ADD_VARIABLE(cameraTarget, true);
	ADD_VARIABLE(yDistanceMultiplier, true);
	ADD_VARIABLE(zDistanceMultiplier, true);
	ADD_VARIABLE(moveSpeed, true);
	ADD_VARIABLE(rotationSpeed, true);
	ADD_VARIABLE(cameraAngle, true);
	END_REFLECTION();
}
