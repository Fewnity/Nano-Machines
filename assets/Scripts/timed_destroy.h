#pragma once

#include <engine/component.h>

class Prefab;

class TimedDestroy : public Component
{
public:
	void Start() override;
	void Update() override;
	ReflectiveData GetReflectiveData() override;
	float cooldown = 10;

private:
	float timer = 0;
};
