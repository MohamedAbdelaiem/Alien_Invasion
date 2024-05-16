#include "tank.h"
#include "Game.h"


tank::tank(int id):armyUnit(id)
{

	this->Type = Tank;
}

tank::tank(int id, int join_time, int Health, int power, int attackC, unitType type, Game* game):armyUnit(id, join_time, Health, power, attackC, type,game)
{

}

bool tank::Attack()
{

	// ET ID shots [AS IDs] [AM IDs]


	AlienArmy* alienArmyList;        // a list for AlienArmy
	EarthArmy* EarthArmyList;        // a list for EarthArmy
	LinkedQueue<monsters*> templist_AM;  //templist for monsters
	LinkedQueue<AllienSoldier*> templist_AS;  //templist for Alien Soldiers


	alienArmyList = game_ptr->get_aliens_pointer();
	EarthArmyList = game_ptr->get_humans_pointer();
	bool flag_attack = false;
	int i = 0;
	if (!game_ptr->getSilentMode())
	{
		cout << "ET " << this << " shots [ ";        //--> print the attacked units
	}



	// -------------------  Attacking Allien Soldiers if EarthSoldiers count falls below 30% of AllienSoldiers count  ----------------------------

	if ((alienArmyList->getCountForAS() != 0 && (float(EarthArmyList->getCountForES()) / alienArmyList->getCountForAS()) < 0.3) || ((alienArmyList->getCountForAS() != 0) && (EarthArmyList->ET_start_to_attack_AS) && ((float(EarthArmyList->getCountForES()) / alienArmyList->getCountForAS()) < 0.8)))
	{
		armyUnit* AS = new AllienSoldier;   // allocate an AS to do dynamic_cast
		armyUnit* A = AS;

		while ( i < this->attackCapacity / 2)
		{
			alienArmyList->deleteUnit(AS);
			if (AS) {
				AS->set_attacked_time(game_ptr->get_current_time());   //set the first attacked time 
				AS->set_first_attack_delay();                          //set the first attcked delay time

				if (!game_ptr->getSilentMode())
				{
					cout << AS<<" ";        //--> print the attacked AS
				}

				double damage = (float(this->Power) * this->health / 100) / sqrt(AS->getHealth());   //calc the damage
				AS->setHealth(AS->getHealth() - damage);                                     //set the health after the demage
				if (AS->getHealth() > 0)
				{
					templist_AS.enqueue(dynamic_cast<AllienSoldier*> (AS));           // add to the templist if it's alive
				}
				else
				{
					game_ptr->add_to_killed_list(AS);                             // add to the Killedlist if it was killed
				}
				flag_attack = true;
				i++;
			}
			else break;
		}

		delete A;
	}
	 

	AllienSoldier* as;
	if (!game_ptr->getSilentMode())
	{
		cout << "] [";
	}
	while (templist_AS.dequeue(as))
	{
			alienArmyList->addUnit(as);        // moves all units from templist to its original list
	}
	
	if (flag_attack)     //--> check if the tank has attacked the AS or not
	{
		/*  
			after attacking the AS we check if the rate still < 80% then the ETs will continue to attack
			ASs in the next timesteps, else the rate >= 80% ETs will not attack ASs till the rate reaches < 30%
		*/
		if ((alienArmyList->getCountForAS() != 0) && ((float(EarthArmyList->getCountForES()) / alienArmyList->getCountForAS()) >= 0.8)) EarthArmyList->ET_start_to_attack_AS = false;
		else EarthArmyList->ET_start_to_attack_AS = true;
	}




	//---------------------------------------------------  Attacking the monsters  -------------------------------------------------------------


	armyUnit* AM = new monsters;   // allocate an AM to do dynamic_cast
	armyUnit* A = AM;
	while(i<this->attackCapacity)
	{
		alienArmyList->deleteUnit(AM);
		if (AM) {
			AM->set_attacked_time(game_ptr->get_current_time());  //set the first attacked time 
			AM->set_first_attack_delay();                         //set the first attcked delay time

			if (!game_ptr->getSilentMode())
			{
				cout << AM<< " ";        //--> print the attacked units
			}

			double damage = (float(this->Power) * this->health / 100) / sqrt(AM->getHealth());   //calc the damage
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
			i++;
		}
		else break;
	}
	delete A;


	if (!game_ptr->getSilentMode())  
	{
		cout << "]\n";
	}
	monsters* am;
	while (templist_AM.dequeue(am))
	{
		alienArmyList->addUnit(am);        // moves all units that still alive from templist to its original list
	}
	
	return flag_attack;
}


