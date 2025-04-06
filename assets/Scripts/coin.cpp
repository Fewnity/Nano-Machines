#include "coin.h"
#include <xenity.h>

void Coin::Update()
{
	auto transform = GetTransform();
	Vector3 rot = transform->GetEulerAngles();
	rot.y += rotateSpeed * Time::GetDeltaTime();
	transform->SetRotation(rot);
}

void Coin::OnTriggerEnter(CollisionEvent eventData)
{
	// std::shared_ptr<Player> player = eventData.otherCollider->GetGameObject()->GetComponent<Player>();
	// if (player)
	// {
	// 	player->coinCount++;
	// }
	GetGameObject()->SetActive(false);
	std::shared_ptr<GameObject> spawnedParticles = Instantiate(particlesPrefab);
	spawnedParticles->GetTransform()->SetPosition(GetGameObject()->GetTransform()->GetPosition());
	spawnedParticles->GetComponent<ParticleSystem>()->Play();
}

ReflectiveData Coin::GetReflectiveData()
{
	BEGIN_REFLECTION();
	ADD_VARIABLE(rotateSpeed, true);
	ADD_VARIABLE(particlesPrefab, true);
	END_REFLECTION();
}
