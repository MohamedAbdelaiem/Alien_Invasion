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
	bool isEmpty = uml->isEmpty();
	bool attack_flag = false;
	armyUnit* unit;
	if (!game_ptr->getSilentMode())
	{
		cout << "HU " << this << " Heals [ ";        //--> print the attacked units
	}
	for (int i = 0; i < this->attackCapacity; i++)
	{
		if (!uml->isEmpty())
		{
			int x;
			uml->dequeue(unit,x);
			if (game_ptr->get_current_time() - unit->get_time_UML() > 10)
			{
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
				if(!game_ptr->getSilentMode())
						cout<< unit<<" "; //->print the healed unit
				if (float(unit->getHealth()) / unit->getOrigHealth() > 0.2)
				{
					if (unit->get_infection())	
					{
						unit->set_immunity(true);//gives the unit immunity to avoid be infected again
					}
					EarthPtr->addUnit(unit);
					game_ptr->incr_numOfHealedUnits();
				}
				else
				{
					tempList->enqueue(unit);
				}
				attack_flag = true;
			}
		}
		else
		{
			break;
		}
	}
	if (!game_ptr->getSilentMode())
	{
		cout << "]\n";
	}
	while (tempList->dequeue(unit))
	{
		if (earthSoldier* es = dynamic_cast<earthSoldier*> (unit))
		{
			uml->enqueue(es, -1 * es->getHealth());
		}
		else uml->enqueue(unit, -1000);
	}
	if (attack_flag)
	{
		this->setHealth(0);
		this->set_attacked_time(game_ptr->get_current_time());
		game_ptr->add_to_killed_list(this);
	}
	else EarthPtr->addUnit(this);
	delete tempList;
	return attack_flag;
}
