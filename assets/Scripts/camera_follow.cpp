#include "camera_follow.h"
#include <xenity.h>

void CameraFollow::Update()
{
	if(std::shared_ptr<GameObject> targetLock = cameraTarget.lock())
	{
		std::shared_ptr<Transform> transform = GetTransform();
		std::shared_ptr<Transform> targetTransform = targetLock->GetTransform();
		
		// Fix if the camera update if made before the update of the car
		targetTransform->SetEulerAngles(Vector3(0, targetTransform->GetEulerAngles().y, 0));

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
	ADD_VARIABLE(cameraTarget);
	ADD_VARIABLE(yDistanceMultiplier);
	ADD_VARIABLE(zDistanceMultiplier);
	ADD_VARIABLE(moveSpeed);
	ADD_VARIABLE(rotationSpeed);
	ADD_VARIABLE(cameraAngle);
	END_REFLECTION();
}
