#include "monster.h"
#include "Game.h"

using namespace std;

monsters::monsters(int id):armyUnit(id)
{
}

monsters::monsters(int id, int join_time, int Health, int power, int attackC, unitType type, Game* game) :armyUnit(id, join_time, Health, power, attackC,type,game)
{
}

bool monsters::Attack()
{
	LinkedQueue<earthSoldier*>temp_list_soldiers; //temp list for earth soldiers
	ArrayStack<tank*>temp_list_tank; //temp list for earth tanks
	LinkedQueue<armyUnit*>print; //list for printing
	armyUnit* ES = new earthSoldier; //// allocate an ES to do dynamic_cast
	armyUnit* E = ES;
	int i = 0;
	while ( i < attackCapacity / 2)
	{
		game_ptr->get_humans_pointer()->deleteUnit(ES);                             //->delete a unit from its list to attack it
		if (ES) //checking for NULL 
		{
			ES->set_attacked_time(game_ptr->get_current_time());                    //->set the first attacked time
			ES->setHealth(ES->getHealth() - ((Power * health) / 100) / float(sqrt(ES->getHealth())));  //->set the health of the attacked unit with the damage
			ES->set_first_attack_delay(); //->set the first attack delay
			print.enqueue(ES); //->add to print list
			if (float(ES->getHealth()) / ES->getOrigHealth() < 0.2 && ES->getHealth() > 0)            //->check for inserting in UML list
			{
				game_ptr->add_to_UML(ES, -1 * ES->getHealth());                   //->add to uml list and set his piriority
				ES->set_time_UML(game_ptr->get_current_time());                  //->set time for entering the UML
			}
			else if (ES->getHealth() > 0)                                       //->if he didnt killed put it in temp list as a place holder
			{
				temp_list_soldiers.enqueue(dynamic_cast<earthSoldier*>(ES));
			}
			else																//add to killed list
			{
				game_ptr->add_to_killed_list(ES);
			}	
			i++;																//increasing the counter
		}
		else
			break;
	}
	delete E;

	if (!game_ptr->getSilentMode())  
	{
		cout << "AM " << ID << " shots [ ";
		while (!print.isEmpty())
		{
			print.dequeue(E);
			cout << E << " ";
		}
		cout << "] ";
	}
	

	armyUnit* t = new tank;
	E = t;

	while ( i < attackCapacity)
	{
		game_ptr->get_humans_pointer()->deleteUnit(t);                             //->delete a unit from its list to attack it
		if (t) //checking for NULL 
		{
			t->set_attacked_time(game_ptr->get_current_time());                    //->set the first attacked time
			t->setHealth(t->getHealth() - ((Power * health) / 100) / float(sqrt(t->getHealth())));  //->set the health of the attacked unit with the damage
			t->set_first_attack_delay(); //->set the first attack delay
			print.enqueue(t); //->add to print list
			if (float(t->getHealth()) / t->getOrigHealth() < 0.2 && t->getHealth() > 0)            //->check for inserting in UML list
			{
				game_ptr->add_to_UML(t, -1000);                   //->add to uml list and set his piriority
				t->set_time_UML(game_ptr->get_current_time());                  //->set time for entering the UML
			}
			else if (t->getHealth() > 0)                                       //->if he didnt killed put it in temp list as a place holder
			{
				temp_list_tank.push(dynamic_cast<tank*>(t));
			}
			else //->add to killed list
			{
				game_ptr->add_to_killed_list(t);
			}
			i++;  //->increasing the counter
		}
		else
			break;
	}
	delete E;

	if (!game_ptr->getSilentMode())   
	{
		cout << "[ ";
		while (!print.isEmpty())
		{
			print.dequeue(E);
			cout << E << " ";
		}
		cout << "]"<<endl;
	}
	while (!temp_list_soldiers.isEmpty()) //return all soldiers from its templist to its original list
	{
		earthSoldier* ES1;
		temp_list_soldiers.dequeue(ES1);
		game_ptr->get_humans_pointer()->addUnit(ES1);
	}
	while (!temp_list_tank.isEmpty())    //return all tanks from its templist to its original list
	{
		tank* tank;
		temp_list_tank.pop(tank);
		game_ptr->get_humans_pointer()->addUnit(tank);
	}
	if (i == 0)
	{
		return false;
	}
	else
	{
		return true;
	}
}




