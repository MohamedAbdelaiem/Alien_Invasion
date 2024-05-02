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
public:
	EarthArmy();
	virtual void addUnit(armyUnit* unit) ;
	virtual void deleteUnit(armyUnit*& unit) ;
	virtual void print() ;
	virtual void attack() ;
	virtual void Healing();
	virtual int getCountForES() ;//get the number of Earth Soldiers
	bool peek_unit(armyUnit*& unit);
	~EarthArmy();

};
#endif
