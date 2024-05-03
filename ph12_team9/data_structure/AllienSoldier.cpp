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
	LinkedQueue<armyUnit*>temp;
	EarthArmy* EarthA = game_ptr->get_humans_pointer();
	armyUnit* ES = new earthSoldier;
	armyUnit* E = ES;
	int i = 0;
	if (!game_ptr->getSilentMode())
	{
		cout << "AS " << this->ID << " shots [ ";        //--> print the attacked units
	}
	while ((i < this->getAttackCapacity()) && ES)
	{
		EarthA->deleteUnit(ES);
		if (ES)
		{
			if (!game_ptr->getSilentMode())
			cout << ES << " ";
			ES->set_attacked_time(game_ptr->get_current_time());   //set the first attacked time 
			ES->set_first_attack_delay();
			ES->setHealth(ES->getHealth() - (this->Power * this->health / 100) / sqrt(ES->getHealth()));
			if (float(ES->getHealth()) / ES->getOrigHealth() < 0.2 && ES->getHealth() > 0)
			{
				game_ptr->add_to_UML(ES, -ES->getHealth());
				ES->set_time_UML(game_ptr->get_current_time());
			}
			else if (ES->getHealth())
			{
				temp.enqueue(ES);
			}
			else
			{
				game_ptr->add_to_killed_list(ES);
			}
		}
		i++;
	}
	if (!game_ptr->getSilentMode())
	cout << "]\n";
	armyUnit* tempPtr;
	while (temp.dequeue(tempPtr))
	{
		EarthA->addUnit(tempPtr);
	}
	delete E;
}
