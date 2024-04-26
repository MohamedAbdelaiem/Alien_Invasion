#include "AllienSoldier.h"
AllienSoldier::AllienSoldier(int id) :armyUnit(id)
{
}

AllienSoldier::AllienSoldier(int id, int join_time, int Health, int power, int attackC,unitType type,Game* game) :armyUnit(id, join_time, Health, power, attackC,type,game)
{
}
void AllienSoldier::Attack()
{
}
