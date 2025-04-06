#include "timed_destroy.h"
#include <xenity.h>

void TimedDestroy::Start()
{
	timer = cooldown;
}

void TimedDestroy::Update()
{
	timer -= Time::GetUnscaledDeltaTime();
	if(timer <= 0)
	{
		Destroy(GetGameObject());
	}
}

ReflectiveData TimedDestroy::GetReflectiveData()
{
	BEGIN_REFLECTION();
	ADD_VARIABLE(cooldown, true);
	END_REFLECTION();
}
