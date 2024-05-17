#pragma once
#ifndef S_U
#define S_U
#include "armyUnit.h"
using namespace std;
class saverUnit :public armyUnit
{
public:
	saverUnit(int id = 0);
	saverUnit(int id, int join_time, int Health, int power, int attackC, unitType type, Game* game);
	virtual bool Attack();

};

#endif