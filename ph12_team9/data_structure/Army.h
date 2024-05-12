#pragma once
#ifndef ARMY_0 
#define ARMY_0
#include "armyUnit.h"
class Army
{
	
public:
	virtual void addUnit(armyUnit* unit)=0;//add a general unit to its list
	virtual void deleteUnit(armyUnit*& unit) =0;//remove a general unit from its list
	virtual void print() const = 0;//print all lists
	virtual bool attack() = 0;
	virtual bool peek_unit(armyUnit*& unit) const = 0;//peek a general  unit
	virtual int get_count() const =0;
};
#endif
