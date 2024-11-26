#include "game.h"
#include <engine/class_registry/class_registry.h>

//----- Include all your classes here:
#include "Scripts/car.h"

/**
* Register all your classes here:
*/
void Game::Start()
{
	REGISTER_COMPONENT(Car);
}