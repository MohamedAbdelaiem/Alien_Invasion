#include ""

saverUnit::saverUnit(int id): armyUnit(id)
{
}

saverUnit::saverUnit(int id, int join_time, int Health, int power, int attackC, unitType type, Game* game):armyUnit(id, join_time, Health, power, attackC, type, game)
{
}

bool saverUnit::Attack()
{
	return false;
}
