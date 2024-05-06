#pragma once
#ifndef E_S
#define E_S
#include"armyUnit.h"
using namespace std;
class earthSoldier :public armyUnit
{
public:
	earthSoldier(int id=0 );
	earthSoldier(int id, int join_time, int Health, int power, int attackC, unitType type, Game* game);
	virtual bool Attack();

};

#endif