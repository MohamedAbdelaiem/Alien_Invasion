	#include "Heal_Soldier.h"
#include "Game.h"

Heal_Soldier::Heal_Soldier(int id):armyUnit(id)
{
}

Heal_Soldier::Heal_Soldier(int id, int join_time, int Health, int power, int attackC, unitType type, Game* game):armyUnit(id,join_time,Health,power,attackC,type,game)
{
}

bool Heal_Soldier::Attack()
{
	priQueue<armyUnit*>* uml = game_ptr->get_UML();
	LinkedQueue<armyUnit*>* tempList = new LinkedQueue<armyUnit*>;
	EarthArmy* EarthPtr = game_ptr->get_humans_pointer();
	bool attack_flag = false;
	armyUnit* unit;
	if (!game_ptr->getSilentMode())
	{
		cout << "HU " << this << " Heals [ ";        //--> print the attacked units
	}
	for (int i = 0; i < this->attackCapacity && !uml->isEmpty(); )
	{
			int x;
			uml->dequeue(unit,x);
			if (game_ptr->get_current_time() - unit->get_time_UML() > 10)  //--> if the attacked unit spent more than 10 timesteps in the uml we killed it
			{
				if (unit->get_infection())
					game_ptr->decrease_numOfInfectedSoldiersInUML();
				unit->setHealth(0);
				game_ptr->add_to_killed_list(unit);
				
			}
			else
			{
				if (unit->get_infection()) //->check for infected earth soldiers
				{
					unit->setHealth(unit->getHealth() + ((float(this->Power) * this->health / 200) / sqrt(unit->getHealth()))); //healing the infectd slower twice than the normal soldier
				}
				else
					unit->setHealth(unit->getHealth() + ((float(this->Power) * this->health / 100) / sqrt(unit->getHealth())));
				if (!game_ptr->getSilentMode())
					cout << unit << " "; //->print the healed unit
				if (float(unit->getHealth()) / unit->getOrigHealth() > 0.2)  //--> if the healed unit was healed succeefully return it to its original list
				{
					if (unit->get_infection())
					{
						unit->set_immunity(true);//gives the unit immunity to avoid be infected again
						unit->set_infection(false);
						game_ptr->decrease_numOfInfectedSoldiers();
						game_ptr->decrease_numOfInfectedSoldiersInUML();
					}
					EarthPtr->addUnit(unit);
					game_ptr->incr_numOfHealedUnits();
				}
				else
				{
					tempList->enqueue(unit); //--> enquee the healed unit wasn't healed completely put it in a temp list
				}
				attack_flag = true;
				i++;
			}
	}
	if (!game_ptr->getSilentMode())
	{
		cout << "]\n";
	}
	while (tempList->dequeue(unit))   //--> return the units in the temp list to the uml
	{
		if (earthSoldier* es = dynamic_cast<earthSoldier*> (unit))
		{
			uml->enqueue(es, -1 * es->getHealth());
		}
		else uml->enqueue(unit, -1000);
	}
	if (attack_flag)  //--> if the HU heal any unit we kill it after that
	{
		this->setHealth(0);
		this->set_attacked_time(game_ptr->get_current_time());     
		game_ptr->add_to_killed_list(this);
	}
	else EarthPtr->addUnit(this);
	delete tempList;
	return attack_flag;
}
