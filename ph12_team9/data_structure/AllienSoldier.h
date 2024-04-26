#pragma once
#ifndef A_S 
#define A_S
#include "armyUnit.h"
class AllienSoldier : public armyUnit
{
public:
	AllienSoldier(int id = 0);
	AllienSoldier(int id, int join_time, int Health, int power, int attackC,unitType type,Game* game);
	virtual void Attack();
};
#endif
