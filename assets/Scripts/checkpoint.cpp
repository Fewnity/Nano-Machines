#include "checkpoint.h"
#include <xenity.h>

void CheckPoint::OnTriggerEnter(CollisionEvent eventData)
{
	if(!passed)
	{
		// Make particles only once
		std::shared_ptr<GameObject> spawnedParticles = Instantiate(particlesPrefab);
		spawnedParticles->GetTransform()->SetPosition(GetGameObject()->GetTransform()->GetPosition());
		spawnedParticles->GetComponent<ParticleSystem>()->Play();
		passed = true;
	}
}

ReflectiveData CheckPoint::GetReflectiveData()
{
	BEGIN_REFLECTION();
	ADD_VARIABLE(particlesPrefab, true);
	END_REFLECTION();
}
