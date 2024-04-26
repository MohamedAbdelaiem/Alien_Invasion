#include "Gunnery.h"
#include "Game.h"

Gunnery::Gunnery(int id) :armyUnit(id)
{
}

Gunnery::Gunnery(int id, int join_time, int Health, int power, int attackC, unitType type, Game* game) :armyUnit(id, join_time, Health, power, attackC,type,game)
{
}

void Gunnery::Attack()
{
}
