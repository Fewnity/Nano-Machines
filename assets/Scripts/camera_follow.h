#pragma once

#include <engine/component.h>
#include <xenity.h>

class CameraFollow : public Component
{
public:
	std::weak_ptr<GameObject> cameraTarget;
	float moveSpeed = 5.0f;
	float rotationSpeed = 5.0f;

	float yDistanceMultiplier = 3;
	float zDistanceMultiplier = 3;

private:
	void Update() override;
	ReflectiveData GetReflectiveData() override;
	Vector3 cameraAngle;
};
