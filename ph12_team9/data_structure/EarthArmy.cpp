#include "EarthArmy.h"
#include"Game.h"
#include <iostream>
using namespace std;
EarthArmy::EarthArmy()
{
	Gunneries = new priQueue<Gunnery*>;
	soldiers = new LinkedQueue<earthSoldier*>;
	tanks = new ArrayStack<tank*>;
	healing_list = new ArrayStack<Heal_Soldier*>;
}

void EarthArmy::addUnit(armyUnit* unit)
{
	if (earthSoldier* S = (dynamic_cast<earthSoldier*>(unit)))  //Add an Earth Soldier 
	{
		soldiers->enqueue(S);                                      
	}
	else if (tank* T = (dynamic_cast<tank*>(unit)))          //Add a Tank
	{
		tanks->push(T);
	}
	else if (Gunnery* g = (dynamic_cast<Gunnery*>(unit)))       //Add a Gunnary
	{
		Gunneries->enqueue(g,g->getHealth()+g->getPower());//add a gunnery to its list
	}
	
}

void EarthArmy::deleteUnit(armyUnit*& unit)
{
	if (Gunnery* g = (dynamic_cast<Gunnery*>(unit)))     //delete a Gunnery
	{
		int x;
		if(Gunneries->dequeue(g, x))
		unit = g;
		else unit = nullptr;
	}
	
	else if (earthSoldier* es= dynamic_cast<earthSoldier*>(unit))       //delete an Earth Soldier 
	{

		if(soldiers->dequeue(es))
		unit = es;
		else unit = nullptr;
	}
	else                            //delete a Tank
	{
		tank* T;
		if(tanks->pop(T))
		unit = T;
		else unit = nullptr;
	}
}

void EarthArmy::print()
{

	cout << soldiers->get_count() << " ES";         //print soldier list
	soldiers->print_list();

	cout << tanks->get_count() << " ET";          //print Tank list
	tanks->print_list();

	cout << Gunneries->getCount() << " EG ";     //print Gunnery list
	Gunneries->print_list();

	
}

void EarthArmy::attack()
{
	//Attacking for EarthSoldier
	earthSoldier* ES;
	if(soldiers->peek(ES))   //--> peek one EarthSoldier from ES list 
	ES->Attack();        //--> make it attack 
	//============================================
	 
	
	//Attacking for Tank
	tank* ET;
	if(tanks->peek(ET))   //--> peek one Tank from ET list 
	ET->Attack();        //--> make it attack 
	//============================================
	 
	
	//Attacking for Gunnery
	Gunnery* EG;
	int x;
	if(Gunneries->peek(EG,x))   //--> peek one Gunnery from EG list 
	EG->Attack();        //--> make it attack 
	//============================================


}

int EarthArmy::getCountForES()
{
	return this->soldiers->get_count();
}

bool EarthArmy::peek_unit(armyUnit*& unit)
{
	if (Gunnery* g = (dynamic_cast<Gunnery*>(unit)))
	{
		int x;
		if (Gunneries->peek(g,x))       //peek the gunnery wich have the most priority
			unit = g;
		else
		{
			unit = nullptr;
			return false;
		}
	}
	
	else if (earthSoldier* es = dynamic_cast<earthSoldier*>(unit))
	{

		if (soldiers->peek(es))             // peek the oldest earth soldier
			unit = es;                                     
		else
		{
			unit = nullptr;
			return false;
		}
	}
	else
	{
		tank* T;
		if (tanks->peek(T))          //peek the freshest tank
			unit = T;
		else
		{
			unit = nullptr;
			return false;
		}
	}
}

EarthArmy::~EarthArmy()  //Destructor
{

	earthSoldier* es;
	while (soldiers->dequeue(es))
	{
		if(es) delete es;
	}
	Gunnery* eg;
	int i;
	while (Gunneries->dequeue(eg,i))
	{
		if (eg) delete eg;
	}
	Heal_Soldier* HS;
	while (healing_list->pop(HS))
	{
		if (HS) delete HS;
	}
	tank* et;
	while (tanks->pop(et))
	{
		if (et) delete et;
	}
	delete soldiers;
	soldiers = nullptr;
	delete tanks;
	tanks = nullptr;
	delete Gunneries;
	Gunneries = nullptr;
	delete healing_list;
	healing_list = nullptr;
}