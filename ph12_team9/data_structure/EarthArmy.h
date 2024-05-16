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
	virtual void addUnit(armyUnit* unit) ;  //--> add a unit to its appropriate list
	virtual void deleteUnit(armyUnit*& unit) ;  //--> delete a unit
	virtual void print() const ;   //--> print all earth army lists
	virtual bool attack() ;  //--> make all  earth army units attack 
	virtual int getCountForES() ;  //-->get the number of Earth Soldiers
	bool peek_unit(armyUnit*& unit) const;     //--> peek a unit from its list
	virtual int get_count() const;//Get count for the total Army Units
	int RandomInfection(int count);
	~EarthArmy();

};
#endif
