#include "monster.h"
#include "Game.h"

using namespace std;

monsters::monsters(int id):armyUnit(id)
{
	infection_prob = 0;
}

monsters::monsters(int id, int join_time, int Health, int power, int attackC, unitType type, Game* game,int infection) :armyUnit(id, join_time, Health, power, attackC,type,game),infection_prob(infection)
{
}

bool monsters::Attack()
{

	// AM ID shots [ SU IDs ] [ES IDs] [ ET Ids]


	LinkedQueue<earthSoldier*>temp_list_soldiers; //temp list for earth soldiers
	ArrayStack<tank*>temp_list_tank; //temp list for earth tanks
	LinkedQueue<saverUnit*>temp_list_SU; //temp list for saver units
	int i = 0;
	if(!game_ptr->getSilentMode())
		cout << "AM " << ID << " shots [ ";
	// Attacking SU
	armyUnit* SU = new saverUnit;
	armyUnit* E = SU;
	while (i < attackCapacity / 4 && SU)
	{
		game_ptr->get_Ally_pointer()->deleteUnit(SU);                             //->delete a unit from its list to attack it
		if (SU) //checking for NULL 
		{
			SU->set_attacked_time(game_ptr->get_current_time());                    //->set the first attacked time
			SU->setHealth(SU->getHealth() - ((float(Power) * health) / 100) / float(sqrt(SU->getHealth())));  //->set the health of the attacked unit with the damage
			SU->set_first_attack_delay(); //->set the first attack delay
			if (!game_ptr->getSilentMode())
				cout << SU << " ";	//print the attacked unit
			if (SU->getHealth() > 0)                                       //->if he wasn't killed put it in temp list as a place holder
			{
				temp_list_SU.enqueue(dynamic_cast<saverUnit*>(SU));
			}
			else																//add to killed list
			{
				game_ptr->add_to_killed_list(SU);
			}
			i++;																//increasing the counter
		}
	}
	delete E;
	if (!game_ptr->getSilentMode())
		cout << "] [ ";


	//Attacking ES
	armyUnit* ES = new earthSoldier; //// allocate an ES to do dynamic_cast
	 E = ES;
	while ( i < attackCapacity / 2)
	{
		game_ptr->get_humans_pointer()->deleteUnit(ES);                             //->delete a unit from its list to attack it
		if (ES) //checking for NULL 
		{
			ES->set_attacked_time(game_ptr->get_current_time());                    //->set the first attacked time
			ES->setHealth(ES->getHealth() - ((float(Power) * health) / 100) / float(sqrt(ES->getHealth())));  //->set the health of the attacked unit with the damage
			ES->set_first_attack_delay(); //->set the first attack delay
			if (!game_ptr->getSilentMode())
				cout << ES<<" ";	//print the attacked unit
			if (float(ES->getHealth()) / ES->getOrigHealth() < 0.2 && ES->getHealth() > 0)            //->check for inserting in UML list
			{
				game_ptr->add_to_UML(ES, -1 * ES->getHealth());                   //->add to uml list and set his piriority
				ES->set_time_UML(game_ptr->get_current_time());                  //->set time for entering the UML
			}
			else if (ES->getHealth() > 0)                                       //->if he wasn't killed put it in temp list as a place holder
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
	if(!game_ptr->getSilentMode())
		cout << "] [ ";

	armyUnit* t = new tank;
	E = t;

	while ( i < attackCapacity)
	{
		game_ptr->get_humans_pointer()->deleteUnit(t);                             //->delete a unit from its list to attack it
		if (t) //checking for NULL 
		{
			t->set_attacked_time(game_ptr->get_current_time());                    //->set the first attacked time
			t->setHealth(t->getHealth() - ((float(Power) * health) / 100) / float(sqrt(t->getHealth())));  //->set the health of the attacked unit with the damage
			t->set_first_attack_delay(); //->set the first attack delay
			if(!game_ptr->getSilentMode())
				cout<<t<<" "; //-> print the attacked unit
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

	if(!game_ptr->getSilentMode())
		cout << "]" << endl;

	while (!temp_list_soldiers.isEmpty()) //return all soldiers from its templist to its original list
	{
		earthSoldier* ES1;
		temp_list_soldiers.dequeue(ES1);
		int infection = rand() % 101;
		if (infection <= infection_prob) //pro of infect the soldier
		{
			if (!ES1->get_immunity() && !ES1->get_infection()) // if he isn't infected and doesn't have immunity infect it

			{
				ES1->set_infection(true);
				game_ptr->increase_numOfInfectedSoldiers();
				game_ptr->increase_total_number_of_infected(1);
			}
		}
		game_ptr->get_humans_pointer()->addUnit(ES1);
	}
	while (!temp_list_tank.isEmpty())    //return all tanks from its templist to its original list
	{
		tank* tank;
		temp_list_tank.pop(tank);
		game_ptr->get_humans_pointer()->addUnit(tank);
	}
	while (!temp_list_SU.isEmpty())    //return all SU from its templist to its original list
	{
		saverUnit* su;
		temp_list_SU.dequeue(su);
		game_ptr->get_Ally_pointer()->addUnit(su);
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




