#pragma once
#ifndef ARMY_0 
#define ARMY_0
#include "armyUnit.h"
class Army
{
	
public:
	virtual void addUnit(armyUnit* unit)=0;//add a general unit to its list
	virtual void deleteUnit(armyUnit*& unit) =0;//remove a general unit from its list
	virtual void print() = 0;//print all lists
	virtual void attack() = 0;
	virtual bool peek_unit(armyUnit*& unit) = 0;//peek a general  unit
	virtual int get_count()=0;
};
#endif
