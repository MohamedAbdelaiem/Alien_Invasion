#include "monster.h"
#include "Game.h"

using namespace std;

monsters::monsters(int id):armyUnit(id)
{
}

monsters::monsters(int id, int join_time, int Health, int power, int attackC, unitType type, Game* game) :armyUnit(id, join_time, Health, power, attackC,type,game)
{
}

void monsters::Attack()
{
	int remain=0;
	LinkedQueue<earthSoldier*>temp_list_soldiers;
	ArrayStack<tank*>temp_list_tank;
	LinkedQueue<armyUnit*>print;
	for (int i = 0; i < attackCapacity / 2; i++)
	{
		armyUnit* ES = new earthSoldier;
		armyUnit* E=ES;
		game_ptr->get_humans_pointer()->deleteUnit(ES);
		if (ES)
		{
			temp_list_soldiers.enqueue(dynamic_cast<earthSoldier*>(ES));
			print.enqueue(ES);
		}
		else
			break;
		delete E;
	}
	if (!game_ptr->getSilentMode())
	{
		cout << "AM " << ID << " shots [ ";
		while (!print.isEmpty())
		{
			armyUnit* E;
			print.dequeue(E);
			cout << E << " ";
		}
		cout << "] ";
	}
	remain = attackCapacity - temp_list_soldiers.get_count();
	for (int i = 0; i < remain; i++)
	{
		armyUnit* Tank = new tank;
		armyUnit* E=Tank;
		game_ptr->get_humans_pointer()->deleteUnit(Tank);
		if (Tank)
		{
			temp_list_tank.push(dynamic_cast<tank*>(Tank));
			print.enqueue(Tank);
		}
		else	
			break;
		delete E;
	}
	if (!game_ptr->getSilentMode())
	{
		cout << "[ ";
		while (!print.isEmpty())
		{
			armyUnit* E;
			print.dequeue(E);
			cout << E << " ";
		}
		cout << "]" << endl;
	}
	while (!temp_list_soldiers.isEmpty())
	{
		earthSoldier* ES;
		temp_list_soldiers.dequeue(ES);
		ES->set_attacked_time(game_ptr->get_current_time());
		ES->setHealth (ES->getHealth()-((Power * health) / 100) / (sqrt(ES->getHealth())));
		ES->set_first_attack_delay();
		if (float(ES->getHealth()) / ES->getOrigHealth() < 0.2 && ES->getHealth() > 0)
		{
			game_ptr->add_to_UML(ES, -1*ES->getHealth());
			ES->set_time_UML(game_ptr->get_current_time());
		}
		else if (ES->getHealth() > 0)
		{
			game_ptr->get_humans_pointer()->addUnit(ES);
		}
		else
		{
			game_ptr->add_to_killed_list(ES);
		}
	}
	while (!temp_list_tank.isEmpty())
	{
		tank* t;
		temp_list_tank.pop(t);
		t->set_attacked_time(game_ptr->get_current_time());
		t->setHealth(t->getHealth() - ((Power *health) / 100) / (sqrt(t->getHealth())));
		t->set_first_attack_delay();
		if ((float(t->getHealth()) / t->getOrigHealth() < 0.2) && (t->getHealth() > 0))
		{
			game_ptr->add_to_UML(t, -1000);
			t->set_time_UML(game_ptr->get_current_time());
		}
		else if (t->getHealth() == 0)
		{
			game_ptr->add_to_killed_list(t);
		}
		else
		{
			game_ptr->get_humans_pointer()->addUnit(t);
		}
	}

}




