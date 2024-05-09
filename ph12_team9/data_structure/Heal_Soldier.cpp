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
	LinkedQueue<int>* try_to_heal = new LinkedQueue<int>;
	EarthArmy* EarthPtr = game_ptr->get_humans_pointer();
	bool isEmpty = uml->isEmpty();
	bool attack_flag = false;
	armyUnit* unit;
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
				unit->setHealth(unit->getHealth() + ((float(this->Power) * this->health / 100) / sqrt(unit->getHealth())));
				try_to_heal->enqueue(unit->getID());
				if (float(unit->getHealth()) / unit->getOrigHealth() > 0.2)
				{
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
		cout << "HU " << this->ID << " Heals ";
		try_to_heal->print_list();
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
	delete try_to_heal;
	if (attack_flag)
	{
		return true;
	}
	else
	{
		return false;
	}
}
