#include "AllienSoldier.h"
#include "Game.h"

AllienSoldier::AllienSoldier(int id) :armyUnit(id)
{
}

AllienSoldier::AllienSoldier(int id, int join_time, int Health, int power, int attackC,unitType type,Game* game) :armyUnit(id, join_time, Health, power, attackC,type,game)
{
}
void AllienSoldier::Attack()
{
	LinkedQueue<earthSoldier*>temp;
	EarthArmy* EarthA = game_ptr->get_humans_pointer();
	armyUnit* ES = new earthSoldier;
	armyUnit* E = ES;
	EarthA->deleteUnit(ES);
	int i = 0;
	while ((i < this->getAttackCapacity()) && ES)
	{
		temp.enqueue(dynamic_cast<earthSoldier*> (ES));
		ES->set_attacked_time(game_ptr->get_current_time());   //set the first attacked time 
		ES->set_first_attack_delay();
		EarthA->deleteUnit(ES);
		i++;
	}
	if (!game_ptr->getSilentMode())
	{
		cout << "AS " << this->ID << " shots ";        //--> print the attacked units
		temp.print_list();
	}
	earthSoldier* es;
	while (temp.dequeue(es))
	{
		es->setHealth(es->getHealth() - this->getPower());
		if (es->getHealth())
		{
			EarthA->addUnit(es);
		}
		else
		{
			game_ptr->add_to_killed_list(es);
		}
	}
	delete E;
}
