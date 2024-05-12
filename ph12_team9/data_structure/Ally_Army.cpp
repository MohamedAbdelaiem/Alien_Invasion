#include "Ally_Army.h"
#include "Game.h"

// non-default constructor
AllyArmy::AllyArmy(Game* gamePtr)
{
	this->game_ptr = gamePtr;
	SU = new LinkedQueue<saverUnit*>;
}


void AllyArmy::addUnit(armyUnit* unit)
{

	if(saverUnit* su = dynamic_cast<saverUnit*>(unit))
		SU->enqueue(su);          //--> Add saver Unit
}


void AllyArmy::deleteUnit(armyUnit*& unit)
{
	if(saverUnit* su = dynamic_cast<saverUnit*>(unit))
		if (SU->dequeue(su))         //--> check if there is saver units
		{
			unit = su;
			return;
		}
	unit = nullptr;        //--> return nullptr if there is no units to delelte
}



void AllyArmy::print() const
{
	cout << SU->get_count()<< " SU " ;     //--> print SU list
	SU->print_list();
}



bool AllyArmy::attack()
{
	saverUnit* su;
	if(SU->peek(su))    //--> peek saver Unit from SU list 
		return su->Attack();  //--> make it attack
	return false;
}



bool AllyArmy::peek_unit(armyUnit*& unit) const
{
	if (saverUnit* su = dynamic_cast<saverUnit*>(unit))
	{
		if (SU->peek(su))		//--> peek saver unit from SU list
		{
			unit = su;
			return true;  //--> return true if we pick a unit successfully
		}
	}
	unit = nullptr;
	return false;     //--> return false is we didn't find a unit to peek
}



int AllyArmy::get_count() const
{
	return SU->get_count();     //--> return the count of SU list
}



void AllyArmy::destroyAll()
{
	saverUnit* su;
	while (SU->dequeue(su))
	{
		su->set_attacked_time(game_ptr->get_current_time());    //--> set the attacked time to be this time step if it wasn't attacked
		su->set_first_attack_delay();  //--> set the first aattack delay
		su->setHealth(0);      //--> make it's health to be zero   
		game_ptr->add_to_killed_list(su);      //--> add the unit to the killed list
	}
}



AllyArmy::~AllyArmy()
{
	saverUnit* su;
	while (SU->dequeue(su))
	{
		delete su;      // destroy all units
	}
	delete SU;
}
