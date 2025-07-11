#include "coin.h"
#include <xenity.h>

void Coin::Update()
{
	// Rotate the coin
	std::shared_ptr<Transform> transform = GetTransform();
	Vector3 rot = transform->GetEulerAngles();
	rot.y += rotateSpeed * Time::GetDeltaTime();
	transform->SetEulerAngles(rot);
}

void Coin::OnTriggerEnter(CollisionEvent eventData)
{
	GetGameObject()->SetActive(false);
	std::shared_ptr<GameObject> spawnedParticles = Instantiate(particlesPrefab);
	spawnedParticles->GetTransform()->SetPosition(GetGameObject()->GetTransform()->GetPosition());
	spawnedParticles->GetComponent<ParticleSystem>()->Play();
}

ReflectiveData Coin::GetReflectiveData()
{
	BEGIN_REFLECTION();
	ADD_VARIABLE(rotateSpeed);
	ADD_VARIABLE(particlesPrefab);
	END_REFLECTION();
}
