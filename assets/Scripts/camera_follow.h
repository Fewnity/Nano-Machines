#pragma once

#include <engine/component.h>
#include <xenity.h>

class CameraFollow : public Component
{
public:
	CameraFollow();
	void Start() override;
	void Update() override;
	ReflectiveData GetReflectiveData() override;
	std::weak_ptr<GameObject> cameraTarget;
	Vector3 offset = Vector3(3, 4, 3);
	float moveSpeed = 5.0f;

	bool lockX = false;
	bool lockY = false;
	bool lockZ = false;
private:
	Vector3 startPosition = Vector3(0);
};
