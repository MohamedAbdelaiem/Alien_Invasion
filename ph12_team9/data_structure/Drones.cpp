#include "Drones.h"
#include "Game.h"
Drones::Drones(int id):armyUnit(id)
{
}

Drones::Drones(int id, int join_time, int Health, int power, int attackC,unitType type,Game* game) :armyUnit(id,join_time,Health,power,attackC,type,game)
{
}

bool Drones::Attack()
{
	// AD ID shots [ EG IDs ] [ET IDs] 


	ArrayStack<tank*>temp_list_tank;    //temp list for tanks
	LinkedQueue<Gunnery*>temp_list_gunnery; //temp list fir gunneries
	LinkedQueue<int>print;   //List fo printing all attacked units
	armyUnit* EG = new Gunnery;  // allocate an EG to do dynamic_cast
	armyUnit* E = EG;
	int i = 0;
	while ( i < attackCapacity / 2)
	{
		game_ptr->get_humans_pointer()->deleteUnit(EG);                             //->delete a unit from its list to attack it
		if (EG) //checking for NULL 
		{
			EG->set_attacked_time(game_ptr->get_current_time());                    //->set the first attacked time
			EG->setHealth(EG->getHealth() - ((float(Power) * health) / 100) / float(sqrt(EG->getHealth())));  //->set the health of the attacked unit with the damage
			EG->set_first_attack_delay();									//->set the first attack delay
			print.enqueue(EG->getID());												//->add to print list
		    if (EG->getHealth() > 0)                                       //->if he wasn't killed put it in temp list as a place holder
			{
				temp_list_gunnery.enqueue(dynamic_cast<Gunnery*>(EG));
			}
			else //add to killed list
			{
				game_ptr->add_to_killed_list(EG);
			}
			i++;  //increasing the counter
		}
		else
			break;  //EG is NULL pointer
	}
	delete E;
	if (!game_ptr->getSilentMode())
	{
		cout << "AD " << ID << " shots [ ";
		while (!print.isEmpty())
		{
			int E;
			print.dequeue(E);
			cout << E << " ";
		}
		cout << "]";
	}
	armyUnit* t = new tank;
	E = t;
	while (i < attackCapacity)
	{
		game_ptr->get_humans_pointer()->deleteUnit(t);                             //->delete a unit from its list to attack it
		if (t) //checking for NULL 
		{
			t->set_attacked_time(game_ptr->get_current_time());                    //->set the first attacked time
			t->setHealth(t->getHealth() - ((float(Power) * health) / 100) / float(sqrt(t->getHealth())));  //->set the health of the attacked unit with the damage
			t->set_first_attack_delay();														//->set the first attack delay
			print.enqueue(t->getID());																	//->add to print list
			if (float(t->getHealth()) / t->getOrigHealth() < 0.2 && t->getHealth() > 0)            //->check for inserting in UML list
			{
				game_ptr->add_to_UML(t, -1000);                   //->add to uml list and set his piriority
				t->set_time_UML(game_ptr->get_current_time());                  //->set time for entering the UML
			}
			else if (t->getHealth() > 0)                                       //->if he wasn't killed put it in temp list as a place holder
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
			int E;
			print.dequeue(E);
			cout << E << " ";
		}
		cout << "]" << endl;
	}
	while (!temp_list_gunnery.isEmpty())  //return all gunneries from its templist to its original list
	{
		Gunnery* ES1;
		temp_list_gunnery.dequeue(ES1);
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
