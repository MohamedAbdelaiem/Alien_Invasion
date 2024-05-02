#include "Gunnery.h"
#include "Game.h"

Gunnery::Gunnery(int id) :armyUnit(id)
{
}

Gunnery::Gunnery(int id, int join_time, int Health, int power, int attackC, unitType type, Game* game) :armyUnit(id, join_time, Health, power, attackC,type,game)
{
}

void Gunnery::Attack()
{
	AlienArmy* alienArmyList = this->game_ptr->get_aliens_pointer();        // a list for AlienArmy
	armyUnit* AM = new monsters;
	armyUnit* A = AM;
	armyUnit* tempPtr;
	Drones* AD = nullptr;
	LinkedQueue<armyUnit*>temp;
	int i = 0;
	if (!game_ptr->getSilentMode())
	{
		cout << "EG " << this->ID << " shots [ ";        //--> print the attacked units
	}
	while (i < this->getAttackCapacity() / 2 && AM)
	{
		alienArmyList->deleteUnit(AM);
		if (AM)
		{
			if (!game_ptr->getSilentMode())
				cout << AM << " ";
			AM->set_first_attack_delay();
			AM->setHealth(AM->getHealth() - this->getPower());
			if (AM->getHealth())
			{
				temp.enqueue(AM);
			}
			else
				this->game_ptr->add_to_killed_list(AM);
			i++;
		}
		
	}
	if (!game_ptr->getSilentMode())
		cout << "] [ ";
	while (i < this->getAttackCapacity() && alienArmyList->delete_first_or_last_drone(AD))
	{
		if (!game_ptr->getSilentMode())
			cout << AD << " ";
		AD->set_first_attack_delay();
		AD->setHealth(AD->getHealth() - this->getPower());
		if (AD->getHealth())
		{
			temp.enqueue(AD);
		}
		else
			this->game_ptr->add_to_killed_list(AD);
		i++;
	}
	if (!game_ptr->getSilentMode())
		cout << "]\n";
	while (temp.dequeue(tempPtr))
		alienArmyList->addUnit(tempPtr);
	delete A;
}
