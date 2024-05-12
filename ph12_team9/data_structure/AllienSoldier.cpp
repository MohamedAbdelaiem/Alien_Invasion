#include "AllienSoldier.h"
#include "Game.h"

AllienSoldier::AllienSoldier(int id) :armyUnit(id)
{
}

AllienSoldier::AllienSoldier(int id, int join_time, int Health, int power, int attackC,unitType type,Game* game) :armyUnit(id, join_time, Health, power, attackC,type,game)
{
}
bool AllienSoldier::Attack()
{


	// ID AS shots [SU IDs] [ES IDs]

	LinkedQueue<armyUnit*>temp;
	LinkedQueue<armyUnit*>SU_temp;
	EarthArmy* EarthA = game_ptr->get_humans_pointer();
	AllyArmy* allyArmy = game_ptr->get_Ally_pointer();  //--> get pointer to ally army
	armyUnit* ES = new earthSoldier;
	armyUnit* E = ES;

	bool flag_attack = false;
	int i = 0;
	int remains = this->attackCapacity;
	if (!game_ptr->getSilentMode())
	{
		cout << "AS " << this->ID << " shots [ ";        //--> print the attacked units
	}

	//Attacking SU

	armyUnit* SU = new saverUnit;
	armyUnit* S = SU;

	while ((i < this->getAttackCapacity()/2) && SU)
	{
		allyArmy->deleteUnit(SU);        //--> get saver unit from its list and attack it
		if (SU)
		{
			if (!game_ptr->getSilentMode())
				cout << SU << " ";
			SU->set_attacked_time(game_ptr->get_current_time());   //set the first attacked time 
			SU->set_first_attack_delay();
			SU->setHealth(SU->getHealth() - (float(this->Power) * this->health / 100) / sqrt(SU->getHealth()));  //--> set the new health
			if (SU->getHealth()>0)
			{
				SU_temp.enqueue(SU);    //--> enque it tp the temp list if it's still alive
			}
			else
			{
				game_ptr->add_to_killed_list(SU);   //--> add it to killed list if it was killed
			}
			remains--;
			i++;
			flag_attack = true;
		}

	}
	if (!game_ptr->getSilentMode())
		cout << "] [";

	//Attacking ES
	i = remains;
	while (i > 0 && ES)
	{
		EarthA->deleteUnit(ES);
		if (ES)
		{
			if (!game_ptr->getSilentMode())
				cout << ES << " ";
			ES->set_attacked_time(game_ptr->get_current_time());   //set the first attacked time 
			ES->set_first_attack_delay();
			ES->setHealth(ES->getHealth() - (float(this->Power) * this->health / 100) / sqrt(ES->getHealth()));
			if (float(ES->getHealth()) / ES->getOrigHealth() < 0.2 && ES->getHealth() > 0)
			{
				game_ptr->add_to_UML(ES, -1*ES->getHealth());
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
			i--;
			flag_attack = true;
		}
	}
	if (!game_ptr->getSilentMode())
	cout << "]\n";
	armyUnit* tempPtr;
	while (temp.dequeue(tempPtr))
	{
		EarthA->addUnit(tempPtr);
	}
	while (SU_temp.dequeue(tempPtr))
	{
		allyArmy->addUnit(tempPtr);
	}
	delete E;
	delete S;
	
	return flag_attack;
}
