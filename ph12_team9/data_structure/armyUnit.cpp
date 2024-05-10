#include "armyUnit.h"
#include <ostream>
#include"Game.h"
using namespace std;
armyUnit::armyUnit( int id) :ID(id) 
{
    this->setHealth(0);
    this->setPower(0);
    this->setAttackCapacity(0);
    attacked_time = -1;
}
armyUnit::armyUnit(int id, int join_time, int Health, int power, int attackC,unitType type,Game*game)
{
    this->setID(id);
    this->setHealth(Health);
    this->setPower(power);
    this->setAttackCapacity(attackC);
    this->setJoinTime(join_time);
    this->set_unittype(type);
    this-> game_ptr = game;
    attacked_time = -1;
    this->orig_health = Health;
    time_joining_UML = 0;
}
void armyUnit::setID(int id)
{
    ID = id;
}
int armyUnit::getID() const
{
    return ID;
}

void armyUnit::setJoinTime(int time)
{
    if (time >= 0) joinTime = time;
}

int armyUnit::getJoinTime() const
{
    return joinTime;
}

void armyUnit::setHealth(int health)
{
    if (health < 0) this->health = 0;
    else this->health = health;
}

int armyUnit::getHealth() const
{
    return this->health;
}

int armyUnit::getOrigHealth() const
{
    return this->orig_health;
}

void armyUnit::setPower(float power)
{
    if (power >= 0) this->Power = power;
}

float armyUnit::getPower() const
{
    return this->Power;
}

void armyUnit::setAttackCapacity(int AtCap)
{
    if (AtCap > 0) this->attackCapacity = AtCap;
}

int armyUnit::getAttackCapacity() const
{
    return this->attackCapacity;
}

void armyUnit::set_unittype(unitType type)
{
    Type = type;
}

unitType armyUnit::getUnitType() const
{
    return this->Type;
}

void armyUnit::set_attacked_time(int time)
{
   if( attacked_time == -1) this->attacked_time=time;  //set the first attcked time if it's the first time to be attcked
}

int armyUnit::get_attacked_time() const
{
    return attacked_time;
}

void armyUnit::set_destroyed_time(int time)
{
    destroyed_time = time;
}

int armyUnit::get_destroyed_time() const
{
    return destroyed_time;
}

void armyUnit::set_first_attack_delay()
{
    DF = attacked_time - joinTime;
}

void armyUnit::set_destruction_delay()
{
    Dd = destroyed_time - attacked_time;
}

void armyUnit::set_battle_time()
{
    Db = destroyed_time - joinTime;
}

int armyUnit::get_destruction_delay() const
{
    return Dd;
}

int armyUnit::get_first_attack_delay() const
{
    return DF;
}

int armyUnit::get_battle_time() const
{
    return Db;
}

void armyUnit::set_time_UML(int time)
{
    this->time_joining_UML = time;
}

int armyUnit::get_time_UML()
{
    return this->time_joining_UML;
}




ostream& operator<<(ostream& os,   armyUnit* ptr)
{
    os << ptr->getID();
    return os;
}

