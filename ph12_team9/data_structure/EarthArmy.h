#pragma once
#ifndef E_ARMY 
#define E_ARMY
#include "Army.h"
#include "priQueue.h"
#include "Gunnery.h"
#include"ArrayStack.h"
#include "LinkedQueue.h"
#include "earthSoldier.h"
#include "tank.h"
#include"Heal_Soldier.h"
class Game;
class EarthArmy : public Army
{
private:
	priQueue<Gunnery*>* Gunneries;
	LinkedQueue<earthSoldier*>* soldiers;
	ArrayStack<tank*>* tanks;
	ArrayStack<Heal_Soldier*>*HL;
	int ES_total;
	int ET_total;
	int EG_total;
	int HU_total;
public:
	EarthArmy();
	virtual void addUnit(armyUnit* unit) ;
	virtual void deleteUnit(armyUnit*& unit) ;
	virtual void print() ;
	virtual void attack() ;
	virtual int getCountForES() ;//get the number of Earth Soldiers
	bool peek_unit(armyUnit*& unit);
	virtual int get_count();
	int ES_get_count();
	int ET_get_count();
	int EG_get_count();
	int HU_get_count();
	~EarthArmy();

};
#endif
