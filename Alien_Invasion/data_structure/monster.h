#pragma once
#ifndef A_M
#define A_M
#include"armyUnit.h"
using namespace std;
class monsters :public armyUnit
{
public:
	monsters(int id=0);
	monsters(int id, int join_time, int Health, int power, int attackC, unitType type, Game* game,int Infection);
	virtual bool Attack();
	int infection_prob;
};
#endif

