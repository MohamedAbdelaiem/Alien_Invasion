#include "earthSoldier.h"
#include "Game.h"

earthSoldier::earthSoldier(int id):armyUnit(id)
{
	this->Type = earth_soldier;
}

//Non-default constructor
earthSoldier::earthSoldier(int id, int join_time, int Health, int power, int attackC, unitType type, Game* game):armyUnit(id, join_time, Health, power, attackC, type,game)
{
}

bool earthSoldier::Attack()
{
	bool flag_attack = false;

	if (!game_ptr->getSilentMode())
	{
		cout << "ES " << this << " shots [ ";        //--> print the attacked units
	}

	if (this->get_infection()) //infected soldier attacks the other earth soldier
	{
		EarthArmy* EarthArmyList;        // a list for EarthArmy
		LinkedQueue<earthSoldier*> templist;  //templist
		EarthArmyList = this->game_ptr->get_humans_pointer();    //get pointer to the EarthArmy from the game class
		armyUnit* ES = new earthSoldier;   // allocate an ES to do dynamic_cast
		armyUnit* E = ES;
		for (int i = 0; i < this->attackCapacity; i++)
		{
			EarthArmyList->deleteUnit(ES);         //take a ES from its list to be attacked
			if (ES)
			{
				ES->set_attacked_time(game_ptr->get_current_time());   //set the first attacked time 
				ES->set_first_attack_delay();                          //set the first attcked delay time

				if (!game_ptr->getSilentMode())
				{
					cout << ES << " ";  //-> print this attacked unit
				}

				double damage = (float(this->Power) * this->health / 100) / sqrt(ES->getHealth());   //calc the damage
				ES->setHealth(ES->getHealth() - damage);                                     //set the health after the demage
				if (ES->getHealth() > 0)
				{
					templist.enqueue(dynamic_cast<earthSoldier*> (ES));           // add to the templist if it's alive
				}
				else
				{
					game_ptr->add_to_killed_list(ES);                             // add to the Killedlist if it was killed
				}
				flag_attack = true;
			}
			else
			{
				break;
			}
		}
		delete E;
		earthSoldier* es;
		
		while (templist.dequeue(es))
		{
			EarthArmyList->addUnit(es);        // moves all units from templist to its original list
		}
	}
	else
	{
		AlienArmy* alienArmyList;        // a list for AlienArmy
		LinkedQueue<AllienSoldier*> templist;  //templist
		armyUnit* AS = new AllienSoldier;   // allocate an AS to do dynamic_cast
		armyUnit* A = AS;
		alienArmyList = this->game_ptr->get_aliens_pointer();    //get pointer to the AllienArmy from the game class

		for (int i = 0; i < this->attackCapacity; i++)
		{
			alienArmyList->deleteUnit(AS);         //take a AS from its list to be attacked
			if (AS)
			{
				AS->set_attacked_time(game_ptr->get_current_time());   //set the first attacked time 
				AS->set_first_attack_delay();                          //set the first attcked delay time

				if (!game_ptr->getSilentMode())
				{
					cout << AS << " ";  //-> print this attacked unit
				}

				double damage = (float(this->Power) * this->health / 100) / sqrt(AS->getHealth());   //calc the damage
				AS->setHealth(AS->getHealth() - damage);                                     //set the health after the demage
				if (AS->getHealth() > 0)
				{
					templist.enqueue(dynamic_cast<AllienSoldier*> (AS));           // add to the templist if it's alive
				}
				else
				{
					game_ptr->add_to_killed_list(AS);                             // add to the Killedlist if it's killed
				}
				flag_attack = true;
			}
			else
			{
				break;
			}
		}
		delete A;
		AllienSoldier* as;
		while (templist.dequeue(as))
		{
			alienArmyList->addUnit(as);        // moves all units from templist to its original list
		}
	}

	if (!game_ptr->getSilentMode())
	{
		cout << "] \n";  
	}

	return flag_attack;
}

