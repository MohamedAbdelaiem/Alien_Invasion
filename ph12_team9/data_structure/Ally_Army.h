#pragma once
#ifndef Ally_ARMY 
#define Ally_ARMY
#include "Army.h"
#include "LinkedQueue.h"
#include "saverUnit.h"

class Game;
class AllyArmy :public Army
{
private:
	LinkedQueue<saverUnit*>* SU;       //--> list that contain saver units (SU List)
	Game* game_ptr;        //--> pointer to class game
public:
	AllyArmy(Game* gamePtr);    //--> non-default constructor
	virtual void addUnit(armyUnit* su) ;	//--> add a SU to its list
	virtual void deleteUnit(armyUnit*& su) ;	//-->remove a SU unit from its list
	virtual void print() const ;		//--> print SU list
	virtual bool attack() ;		//--> make a sever unit attack enemies
	virtual bool peek_unit(armyUnit*& unit) const ;	//--> peek a sever unit
	virtual int get_count() const ;		//--> get count for all saver units
	virtual void destroyAll();   //--> destroy All saver units
	~AllyArmy();    //--> Destructor
};
#endif
