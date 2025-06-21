#include "game.h"

#include <engine/class_registry/class_registry.h>

//----- Include all your classes here:
#include "Scripts/car.h"
#include "Scripts/camera_follow.h"
#include "Scripts/coin.h"
#include "Scripts/checkpoint.h"
#include "Scripts/timed_destroy.h"

/**
* Register all your classes here:
*/
void Game::Start()
{
	REGISTER_COMPONENT(Car, false);
	REGISTER_COMPONENT(CameraFollow, false);
	REGISTER_COMPONENT(Coin, false);
	REGISTER_COMPONENT(CheckPoint, true);
	REGISTER_COMPONENT(TimedDestroy, false);
}