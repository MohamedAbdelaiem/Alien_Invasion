#include "EarthArmy.h"
#include"Game.h"
#include <iostream>
using namespace std;
EarthArmy::EarthArmy()
{
	Gunneries = new priQueue<Gunnery*>;
	soldiers = new LinkedQueue<earthSoldier*>;
	tanks = new ArrayStack<tank*>;
	HL = new ArrayStack<Heal_Soldier*>;
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
		
		Gunneries->enqueue(g,g->getHealth()+g->getPower());  //add a gunnery to its list
	}
	else
	{
		Heal_Soldier* HU = dynamic_cast<Heal_Soldier*>(unit);  // Add Heal unit to HL
		if (HU)
		{
			HL->push(HU);
		}
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
	else if (Heal_Soldier* HU = dynamic_cast<Heal_Soldier*>(unit))  // delete Heal unit
	{

		if (HL->pop(HU))
			unit = HU;
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

	cout << HL->get_count() << " HU ";     //print HL
	HL->print_list();

	
}

bool EarthArmy::attack()
{
	//flags for attacking functions
	bool flag1 = false;
	bool flag2 = false;
	bool flag3 = false;
	//========================================================================//
	//Attacking for EarthSoldier
	earthSoldier* ES;
	if(soldiers->peek(ES))   //--> peek one EarthSoldier from ES list 
		flag1=ES->Attack();        //--> make it attack 
	//============================================
	 
	
	//Attacking for Tank
	tank* ET;
	if(tanks->peek(ET))   //--> peek one Tank from ET list 
		flag2=ET->Attack();        //--> make it attack 
	//============================================
	 
	
	//Attacking for Gunnery
	Gunnery* EG;
	int x;
	if(Gunneries->peek(EG,x))   //--> peek one Gunnery from EG list 
		flag3=EG->Attack();        //--> make it attack 
	//============================================
	Heal_Soldier* HU;
	if (HL->pop(HU))
	{
		HU->Attack();
	}
	return(flag1 || flag2 || flag3);

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
	else if (Heal_Soldier* HU = dynamic_cast<Heal_Soldier*>(unit)) 
	{
		if (HL->peek(HU))             // peek the freshest HU
			unit = HU;
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

int EarthArmy::get_count()
{
	return soldiers->get_count()+Gunneries->getCount()+ tanks->get_count();
}

int EarthArmy::RandomInfection(int count)  //random infect EarthSolddier 
{
	int infected_index, counter = 0;
	earthSoldier* tempES;
	LinkedQueue<earthSoldier*>tempQ;
	for (int i = 0; i < count; i++)         //every infected EarthSoldier can infect another soldier
	{
		if ((rand() % 101) <= 2)             //prob of random infection
		{
			infected_index = rand() % soldiers->get_count();
			for (int j = 0; j < soldiers->get_count(); j++)
			{
				soldiers->dequeue(tempES);
				if (infected_index == i)
				{
					if (!tempES->get_immunity()&&!tempES->get_infection())
					{
						tempES->set_infection(true);
						counter++;
					}
				}
				tempQ.enqueue(tempES);
			}
			while (tempQ.dequeue(tempES))
			{
				soldiers->enqueue(tempES);
			}
		}
	}
	return counter;   //return number of new infected soldiers
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
	Heal_Soldier* HU;
	while (HL->pop(HU))
	{
		if (HU) delete HU;
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
	delete HL;
	HL = nullptr;
}
