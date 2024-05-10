#include "Gunnery.h"
#include "Game.h"

Gunnery::Gunnery(int id) :armyUnit(id)
{
}

Gunnery::Gunnery(int id, int join_time, int Health, int power, int attackC, unitType type, Game* game) :armyUnit(id, join_time, Health, power, attackC,type,game)
{
}

bool Gunnery::Attack()
{
	AlienArmy* alienArmyList = this->game_ptr->get_aliens_pointer();        // a pointer for AlienArmy
	armyUnit* AM = new monsters;
	armyUnit* A1 = AM;
	armyUnit* tempPtr;
	armyUnit* AD = new Drones;
	armyUnit* A2 = AD;
	LinkedQueue<armyUnit*>temp;
	QUEUE<armyUnit*>tempDrones;
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
			AM->set_attacked_time(game_ptr->get_current_time());
			AM->set_first_attack_delay();
			AM->setHealth(AM->getHealth() - (this->Power * this->health / 100) / sqrt(AM->getHealth()));
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
	while (i < this->getAttackCapacity() && AD)
	{
		alienArmyList->deleteUnit(AD);
		if (AD)
		{
			if (!game_ptr->getSilentMode())
				cout << AD << " ";
			AD->set_attacked_time(game_ptr->get_current_time());
			AD->set_first_attack_delay();
			AD->setHealth(AD->getHealth() - (this->Power * this->health / 100) / sqrt(AD->getHealth()));
			if (AD->getHealth())
			{
				tempDrones.enqueue_first_last(AD);
			}
			else
				this->game_ptr->add_to_killed_list(AD);
			i++;
		}
	}
	if (!game_ptr->getSilentMode())
		cout << "]\n";
	while (temp.dequeue(tempPtr))
		alienArmyList->addUnit(tempPtr);
	while (tempDrones.delete_first_or_last(tempPtr))
		alienArmyList->addUnit(tempPtr);
	delete A1;
	delete A2;
	if (i == 0)
	{
		return false;
	}
	else
	{
		return true;
	}
}
