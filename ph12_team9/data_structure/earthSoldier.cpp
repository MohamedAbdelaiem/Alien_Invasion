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
	AlienArmy* alienArmyList;        // a list for AlienArmy
	LinkedQueue<AllienSoldier*> templist;  //templist
	LinkedQueue<AllienSoldier*> print;  //list for all attacked units by this ES at this time step
	armyUnit* AS = new AllienSoldier;   // allocate an AS to do dynamic_cast
	armyUnit* A = AS;
	bool flag_attack=false;
	alienArmyList = this->game_ptr->get_aliens_pointer();    //get pointer to the AllienArmy from the game class
	
	for (int i = 0; i < this->attackCapacity; i++)
	{
		alienArmyList->deleteUnit(AS);         //take a AS from its list to be attacked
		if (AS)
		{
			AS->set_attacked_time(game_ptr->get_current_time());   //set the first attacked time 
			AS->set_first_attack_delay();                          //set the first attcked delay time

			print.enqueue(dynamic_cast <AllienSoldier*> (AS));     //add this AS to the print list

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
	if (!game_ptr->getSilentMode())
	{
		cout << "ES " << this << " shots ";        //--> print the attacked units
		print.print_list();
	}
	while (templist.dequeue(as))
	{
		alienArmyList->addUnit(as);        // moves all units from templist to its original list
	}
	if (flag_attack)
	{
		return true;
	}
	else
	{
		return false;
	}

}


