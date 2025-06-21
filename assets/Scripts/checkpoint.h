#pragma once

#include <engine/component.h>

class Prefab;

class CheckPoint : public Component
{
public:

private:
	void OnTriggerEnter(CollisionEvent eventData) override;
	ReflectiveData GetReflectiveData() override;

	std::shared_ptr<Prefab> particlesPrefab;
	bool passed = false;
};
