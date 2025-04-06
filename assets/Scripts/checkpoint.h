#pragma once

#include <engine/component.h>

class Prefab;

class CheckPoint : public Component
{
public:
	void Update() override;
	ReflectiveData GetReflectiveData() override;

private:
	void OnTriggerEnter(CollisionEvent eventData) override;

	std::shared_ptr<Prefab> particlesPrefab;
	bool passed = false;
};
