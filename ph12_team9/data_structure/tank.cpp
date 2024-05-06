#include "tank.h"
#include "Game.h"


tank::tank(int id):armyUnit(id)
{
	start_to_attack_AS = false;
	this->Type = Tank;
}

tank::tank(int id, int join_time, int Health, int power, int attackC, unitType type, Game* game):armyUnit(id, join_time, Health, power, attackC, type,game)
{
	start_to_attack_AS = false;
}

bool tank::Attack()
{

	AlienArmy* alienArmyList;        // a list for AlienArmy
	EarthArmy* EarthArmyList;        // a list for EarthArmy
	LinkedQueue<monsters*> templist_AM;  //templist for monsters
	LinkedQueue<AllienSoldier*> templist_AS;  //templist for Alien Soldiers
	LinkedQueue<AllienSoldier*> print_AS;  //list for all attacked AS units by this ET at this time step
	LinkedQueue<monsters*> print_AM;  //list for all attacked AM units by this ET at this time step
	int remain = attackCapacity;
	bool flag_attack = false;
	alienArmyList = game_ptr->get_aliens_pointer();
	EarthArmyList = game_ptr->get_humans_pointer();

	// Attacking Allien Soldiers if EarthSoldiers count falls below 30% of AllienSoldiers count
	if ((alienArmyList->getCountForAS() != 0 && (float(EarthArmyList->getCountForES()) / alienArmyList->getCountForAS()) < 0.3) || ((this->start_to_attack_AS) && (float(EarthArmyList->getCountForES()) / alienArmyList->getCountForAS()) < 0.8))
	{
		armyUnit* AS = new AllienSoldier;   // allocate an AS to do dynamic_cast
		armyUnit* A = AS;
		for (int i = 0; i < this->attackCapacity / 2; i++)
		{
			alienArmyList->deleteUnit(AS);
			if (AS) {
				AS->set_attacked_time(game_ptr->get_current_time());   //set the first attacked time 
				AS->set_first_attack_delay();                          //set the first attcked delay time

				print_AS.enqueue(dynamic_cast <AllienSoldier*> (AS));     //add this AS to the print list

				double damage = (this->Power * this->health / 100) / sqrt(AS->getHealth());   //calc the damage
				AS->setHealth(AS->getHealth() - damage);                                     //set the health after the demage
				if (AS->getHealth() > 0)
				{
					templist_AS.enqueue(dynamic_cast<AllienSoldier*> (AS));           // add to the templist if it's alive
				}
				else
				{
					game_ptr->add_to_killed_list(AS);                             // add to the Killedlist if it's killed
				}
				flag_attack = true;
				remain--;
			}
			else break;
		}
		delete A;
		if ((float(EarthArmyList->getCountForES()) / alienArmyList->getCountForAS()) >= 0.8) this->start_to_attack_AS = false;
		else this->start_to_attack_AS = true;
	}
	 
	//print the attacked AllienSoldiers
	AllienSoldier* as;
	if (!game_ptr->getSilentMode())
	{
		cout << "ET " << this->ID << " shots [ ";        //--> print the attacked units
		while (print_AS.dequeue(as))
		{
			cout << as->getID() << " ";
		}
		cout << "]";
	}
	while (templist_AS.dequeue(as))
	{
			alienArmyList->addUnit(as);        // moves all units from templist to its original list
	}
	

	//Attacking the monsters
	armyUnit* AM = new monsters;   // allocate an AM to do dynamic_cast
	armyUnit* A = AM;
	for (int i = 0; i < remain; i++)
	{
		alienArmyList->deleteUnit(AM);
		if (AM) {
			AM->set_attacked_time(game_ptr->get_current_time());  //set the first attacked time 
			AM->set_first_attack_delay();                         //set the first attcked delay time

			print_AM.enqueue(dynamic_cast <monsters*> (AM));      //add this AM to the print list

			double damage = (this->Power * this->health / 100) / sqrt(AM->getHealth());   //calc the damage
			AM->setHealth(AM->getHealth() - damage);              //set the health after the demage
			if (AM->getHealth() > 0)
			{
				templist_AM.enqueue(dynamic_cast<monsters*> (AM));// add to the templist if it's alive
			}
			else
			{
				game_ptr->add_to_killed_list(AM);                 // add to the Killedlist if it's killed
			}
			flag_attack = true;
		}
		else break;
	}
	delete A;

	//print the attacked Monsters
	monsters* am; 
	if(!game_ptr->getSilentMode())print_AM.print_list();          //--> print the attacked units
	while (templist_AM.dequeue(am))
	{
		alienArmyList->addUnit(am);        // moves all units from templist to its original list
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


