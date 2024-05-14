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
	AlienArmy* alienArmyList = this->game_ptr->get_aliens_pointer();												// a pointer for AlienArmy
	armyUnit* AM = new monsters;																					//--> pre initialize to the dynamic cast
	armyUnit* A1 = AM;																								//--> to delete it later
	armyUnit* tempPtr;
	armyUnit* AD = new Drones;																						//--> pre initialize to the dynamic cast
	armyUnit* A2 = AD;																								//--> to delete it later
	LinkedQueue<armyUnit*>tempMonster;																				//--> the temp list of monsters to return it to it's original list
	LinkedQueue<armyUnit*>printD;																					//--> list to print all drones that have been attacked
	LinkedQueue<armyUnit*>printM;																					//--> list to print all monsters that have been attacked
	QUEUE<armyUnit*>tempDrones;																						//--> the temp list of drones to return it to it's original list
	int i = 0;																										//--> counter
	while (i < this->getAttackCapacity() / 2 && AM)																	//--> start attcking alien monsters up to 50% of gunnery capacity
	{
		alienArmyList->deleteUnit(AM);																				//--> getting monster
		if (AM)																										//--> if he isn't nullptr attack him
		{
			printM.enqueue(AM);																						//--> adding him to the print list
			AM->set_attacked_time(game_ptr->get_current_time());													//-->set the first attacked time
			AM->set_first_attack_delay();																			//-->set the first attack delay
			AM->setHealth(AM->getHealth() - (this->Power * this->health / 100) / sqrt(AM->getHealth()));			//->set the health of the attacked unit with the damage
			if (AM->getHealth())																					//--> if he didn't die move him to the temp list
			{
				tempMonster.enqueue(AM);
			}
			else																									//--> if he died move him to the killed list
				this->game_ptr->add_to_killed_list(AM);
			i++;																									//--> updating the counter
		}
		
	}
	alienArmyList->set_starting_dequeue_drones_first();																//-->to make sure to dequeue from fist of the drones QUEUE
	while (i < this->getAttackCapacity() && AD)																		//--> start attcking alien drones to the rest of gunnery capacity
	{
		alienArmyList->deleteUnit(AD);																				//--> getting drone
		if (AD)																										//--> if he isn't nullptr attack him
		{

			printD.enqueue(AD);																						//--> adding him to the print list
			AD->set_attacked_time(game_ptr->get_current_time());													//-->set the first attacked time
			AD->set_first_attack_delay();																			//-->set the first attack delay
			AD->setHealth(AD->getHealth() - (this->Power * this->health / 100) / sqrt(AD->getHealth()));			//->set the health of the attacked unit with the damage
			if (AD->getHealth())																					//--> if he didn't die move him to the temp list
			{
				tempDrones.enqueue_first_last(AD);
			}
			else																									//--> if he died move him to the killed list
				this->game_ptr->add_to_killed_list(AD);
			i++;
		}
	}

	AM = A1;
	while (i < this->getAttackCapacity() && AM)																		//--> if there still attacking capacity attack monster again
	{
		alienArmyList->deleteUnit(AM);
		if (AM)
		{
			printM.enqueue(AM);
			AM->set_attacked_time(game_ptr->get_current_time());
			AM->set_first_attack_delay();
			AM->setHealth(AM->getHealth() - (this->Power * this->health / 100) / sqrt(AM->getHealth()));
			if (AM->getHealth())
			{
				tempMonster.enqueue(AM);
			}
			else
				this->game_ptr->add_to_killed_list(AM);
			i++;
		}

	}
	if (!game_ptr->getSilentMode())
	{
		cout << "EG " << this->ID << " shots [ ";																			 //--> print the attacked units
		while (printM.dequeue(AM))
			cout << AM << " ";
		cout << "] [ ";
		while (printD.dequeue(AD))
			cout << AD << " ";
		cout << "] \n";
	}
	while (tempMonster.dequeue(tempPtr))																					//--> return it back to its original list
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
