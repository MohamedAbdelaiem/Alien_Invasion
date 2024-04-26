#include "AlienArmy.h"
#include<iostream>
#include"Game.h"
using namespace std;
AlienArmy::AlienArmy()
{
	array_monsters = new Array<monsters*>;
	queue_drones = new QUEUE<Drones*>;
	allien_soldier = new LinkedQueue<AllienSoldier*>;
	
}

void AlienArmy::addUnit(armyUnit* unit)
{
	if(monsters*m=(dynamic_cast<monsters*>(unit)))
	{
		array_monsters->insert(m);//add a monster to its list
	}
	else if (Drones* d = dynamic_cast<Drones*>(unit))
	{
		queue_drones->enqueue_first_last(d);//add a drone to its list
	}
	else
	{
		allien_soldier->enqueue(dynamic_cast<AllienSoldier*>(unit));//add a soldier to its list
	}
}

void AlienArmy::deleteUnit(armyUnit*& unit)
{
	if (monsters* m = (dynamic_cast<monsters*>(unit)))
	{
		if (!array_monsters->isEmpty())
		{
			int index = rand() % array_monsters->get_count();
			if (array_monsters->remove(index, m))//delete a random monster from its list
				unit = m;
		}
		else 
	         unit = nullptr;

	}
	else if (Drones* d = dynamic_cast<Drones*>(unit))
	{
		if(queue_drones->dequeue(d))
		unit = d;
		else unit = nullptr;
	}
	else
	{
		AllienSoldier* S = dynamic_cast<AllienSoldier*>(unit);
		if(allien_soldier->dequeue(S))
		unit = S;
		else unit = nullptr;
	}

}

void AlienArmy::print()
{
	cout << "==============Alien Army Alive Units=======================" << endl;
	cout << allien_soldier->get_count() << " AS ";
	allien_soldier->print_list();
	cout << array_monsters->get_count() << " AM "; 
	array_monsters->display();
	cout <<queue_drones->get_count()<< " AD ";
	queue_drones->print_list();
}

void AlienArmy::attack()						
{
	armyUnit* m = new monsters;
	armyUnit* E=m;
	if (peek_unit(m))
	{
		m->Attack();
	}
	delete E;
	armyUnit* D1 = new Drones;
	armyUnit* D2 = new Drones;
	E = D1;
	armyUnit* E2 = D2;
	if (peek_two_drones(D1, D2))
	{
		D1->Attack();
		D2->Attack();
	}
	delete E, E2;


}
int AlienArmy::getCountForAS()
{
	return this->allien_soldier->get_count();
}
bool AlienArmy::delete_two_drones(armyUnit*& drone1, armyUnit*& drone2)
{
	Drones* d1 = dynamic_cast<Drones*>(drone1);
	Drones* d2 = dynamic_cast<Drones*>(drone2);
	if (queue_drones->dequeue_last_first(d1, d2))
	{
		drone1 = d1;
		drone2 = d2;
		return true;
	}
	else
	{
		drone1 = drone2 = nullptr;
		return false;
	}
}

bool AlienArmy::peek_two_drones(armyUnit*& drone1, armyUnit*& drone2)
{
	Drones* d1 = dynamic_cast<Drones*>(drone1);
	Drones* d2 = dynamic_cast<Drones*>(drone2);
	if (queue_drones->peek_last_first(d1, d2))
	{
		drone1 = d1;
		drone2 = d2;
		return true;
	}
	else
	{
		drone1 = drone2 = nullptr;
		return false;
	}
}

bool AlienArmy::peek_unit(armyUnit*& unit)
{
	if (monsters* m = (dynamic_cast<monsters*>(unit)))
	{
		if (!array_monsters->isEmpty())
		{
			int index = rand() % array_monsters->get_count();
			array_monsters->peek(m, index);
			unit = m;
		}
		else
		{
			unit = nullptr;
			return false;
		}

	}
	else if (Drones* d = dynamic_cast<Drones*>(unit))
	{
		if (queue_drones->peek(d))
			unit = d;
		else
		{
			unit = nullptr;
			return false;
		}
	}
	else
	{
		AllienSoldier* S = dynamic_cast<AllienSoldier*>(unit);
		if (allien_soldier->peek(S))
			unit = S;
		else
		{
			unit = nullptr;
			return false;
		}
	}
	return true;
}

AlienArmy::~AlienArmy()
{
	monsters* am;
	int i = 0;
	while (i< array_monsters->get_count())
	{
		array_monsters->remove(i, am);
		if(am) delete am;
		i++;
	}
	AllienSoldier* as;
	while (allien_soldier->dequeue(as))
	{
		if (as) delete as;
	}
	Drones* AD;
	while (queue_drones->dequeue(AD))
	{
		if (AD) delete AD;
	}
	delete array_monsters;
	array_monsters = nullptr;
	delete queue_drones;
	queue_drones = nullptr;
	delete allien_soldier;
	allien_soldier = nullptr;
}