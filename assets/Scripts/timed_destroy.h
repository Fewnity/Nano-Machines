#pragma once

#include <engine/component.h>

class Prefab;

class TimedDestroy : public Component
{
public:
	float cooldown = 10;

private:
	void Start() override;
	void Update() override;
	ReflectiveData GetReflectiveData() override;
	
	float timer = 0;
};
