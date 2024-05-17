#pragma once
#ifndef E_G 
#define E_G
#include "armyUnit.h"
class Gunnery : public armyUnit
{
public:
	Gunnery (int id = 0);
	Gunnery(int id, int join_time, int Health, int power, int attackC, unitType type, Game* game);
	virtual bool Attack();
};
#endif

