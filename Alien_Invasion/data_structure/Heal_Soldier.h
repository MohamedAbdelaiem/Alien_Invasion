#pragma once
#ifndef H_U
#define H_U
#include<iostream>
#include"armyUnit.h"
class Heal_Soldier:public armyUnit
{
public:
	Heal_Soldier(int id = 0);
	Heal_Soldier(int id, int join_time, int Health, int power, int attackC, unitType type, Game* game);
	virtual bool Attack();
};
#endif