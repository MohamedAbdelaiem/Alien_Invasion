#include "Heal_Soldier.h"
#include "Game.h"

Heal_Soldier::Heal_Soldier(int id):armyUnit(id)
{
}

Heal_Soldier::Heal_Soldier(int id, int join_time, int Health, int power, int attackC, unitType type, Game* game):armyUnit(id,join_time,Health,power,attackC,type,game)
{
}

void Heal_Soldier::Attack()
{
	priQueue<armyUnit*>* uml = game_ptr->get_UML();
	LinkedQueue<armyUnit*>* tempList = new LinkedQueue<armyUnit*>;
	EarthArmy* EarthPtr = game_ptr->get_humans_pointer();
	armyUnit* unit;
	for (int i = 0; i < this->attackCapacity; i++)
	{
		if (!uml->isEmpty())
		{
			int x;
			uml->dequeue(unit,x);
			if (game_ptr->get_current_time() - unit->get_time_UML() >= 10)
			{
				unit->setHealth(0);
				game_ptr->add_to_killed_list(unit);
			}
			else
			{

				unit->setHealth(unit->getHealth() + ((this->Power * this->health / 100) / abs(unit->getHealth())));
				if (float(unit->getHealth()) / unit->getOrigHealth() > 0.2)
				{
					EarthPtr->addUnit(unit);
				}
				else
				{
					tempList->enqueue(unit);
				}
				game_ptr->incr_numOfHealedUnits();
			}
		}
		else
		{
			break;
		}
	}
	cout << "HU " << this->ID << " Heals ";
	tempList->print_list();
	while (tempList->dequeue(unit))
	{
		if (earthSoldier* es = dynamic_cast<earthSoldier*> (unit))
		{
			uml->enqueue(es, -1 * es->getHealth());
		}
		else uml->enqueue(unit, -1000);
	}
	this->setHealth(0);
	game_ptr->add_to_killed_list(this);
	delete tempList;
}
