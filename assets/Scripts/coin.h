#pragma once

#include <engine/component.h>

class Prefab;

class Coin : public Component
{
public:
	float rotateSpeed = 10;

private:
	void OnTriggerEnter(CollisionEvent eventData) override;
	void Update() override;
	ReflectiveData GetReflectiveData() override;

	std::shared_ptr<Prefab> particlesPrefab;
};
