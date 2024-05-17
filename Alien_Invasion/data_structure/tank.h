#pragma once
#ifndef E_T
#define E_T
#include"armyUnit.h"
using namespace std;
class tank :public armyUnit
{

public:
	tank(int id=0);
	tank(int id, int join_time, int Health, int power, int attackC, unitType type, Game* game);
	virtual bool Attack();  //--> make the tank attack
};

#endif