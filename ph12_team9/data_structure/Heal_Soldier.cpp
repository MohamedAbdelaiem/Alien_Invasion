#include "Heal_Soldier.h"
#include "Game.h"

Heal_Soldier::Heal_Soldier(int id):armyUnit(id)
{
}

Heal_Soldier::Heal_Soldier(int id, int join_time, int Health, int power, int attackC, unitType type, Game* game):armyUnit(id,join_time,Health,power,attackC,type,game)
{
}

void Heal_Soldier::Attack()
{
}
