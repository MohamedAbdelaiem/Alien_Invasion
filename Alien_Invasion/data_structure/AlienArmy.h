#pragma once
#ifndef A_ARMY 
#define A_ARMY
#include "Army.h"
#include"Array.h"
#include"QUEUE.h"
#include"Drones.h"
#include"monster.h"
#include "AllienSoldier.h"
#include"LinkedQueue.h"
class Game;
class AlienArmy :public Army
{
private:
	//modified array to the monsters
	Array<monsters*>* array_monsters;
	//modified queue to drones
	QUEUE<Drones*>* queue_drones;
	//queue to alien soldiers
	LinkedQueue<AllienSoldier*>* allien_soldier;
	bool flag_delete_drone; 
	
public:
	AlienArmy();
	virtual void addUnit(armyUnit* unit);//add a general unit to its list
	virtual void deleteUnit(armyUnit*& unit);//remove a general unit from its list
	virtual void print() const;//print all lists
	virtual bool attack();//attack earth army
	virtual int getCountForAS() const;//Get the number of Alien Soldiers
	bool delete_two_drones(armyUnit*& drone1, armyUnit*& drone2);//delete two units(drones)
	bool delete_first_or_last_drone(Drones*& drone1);//delete drone once from front and once from back
	bool peek_two_drones(armyUnit*& drone1, armyUnit*& drone2);//peek two units(drones)
	bool peek_unit(armyUnit*& unit) const;//peek a general  unit
	virtual int get_count() const;		//Get count for the total Army Units
	void set_starting_dequeue_drones_first(); //-->to make sure to dequeue from fist of the drones QUEUE
	~AlienArmy();
};
#endif
