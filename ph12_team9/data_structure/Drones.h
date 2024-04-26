#pragma once
#ifndef A_D 
#define A_D
#include"armyUnit.h"
using namespace std;
class Drones :public armyUnit
{
public:
	Drones(int id=0);
	Drones(int id, int join_time, int Health, int power, int attackC, unitType type, Game* game);
	virtual void Attack();
};
#endif