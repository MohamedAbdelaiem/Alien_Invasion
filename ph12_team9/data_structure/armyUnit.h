#pragma once
#ifndef AR_UNIT
#define AR_UNIT
#include<iostream>
using namespace std;
enum unitType { earth_soldier, Tank, gunnery, alien_soldier, monster,  drone,Heal_soldier };
class Game;
class armyUnit
{
public:
protected:
	int ID;
	unitType Type;
	int joinTime;
	int health;
	int orig_health;
	float Power;
	int attackCapacity;
	int attacked_time;
	int destroyed_time;
	int DF, Dd, Db;//first attacked delay,destruction delay,battle time
	Game* game_ptr;
	int time_joining_UML;
	bool infection,immunity;
public:
	armyUnit(int id);
	armyUnit(int id, int join_time, int Health, int power, int attackC,unitType type,Game*game );
	//setters and getters to all data types
	virtual void setID(int id);
	virtual int getID() const;
	virtual void setJoinTime(int);
	virtual int getJoinTime()const;
	virtual void setHealth(int);
	virtual int getHealth()const;
	virtual int getOrigHealth() const;
	virtual void setPower(float);
	virtual float getPower()const;
	virtual void setAttackCapacity(int);
	virtual int getAttackCapacity()const;
	virtual void set_unittype(unitType type);
	virtual unitType getUnitType() const;
	virtual void set_attacked_time(int time);
	virtual int get_attacked_time()const;
	virtual void set_destroyed_time(int time);
	virtual int get_destroyed_time()const;
	virtual void set_destruction_delay();
	virtual void set_first_attack_delay();
	virtual void set_battle_time();
	virtual int get_destruction_delay() const;
	virtual int get_first_attack_delay() const;
	virtual int get_battle_time() const;
	virtual bool Attack()=0;
	void set_time_UML(int time);
	int get_time_UML();
	virtual void set_infection(bool flag);
	virtual bool get_infection() const;
	virtual void set_immunity(bool flag);
	virtual bool get_immunity() const;
	friend ostream& operator<<(ostream& os,armyUnit* ptr);
};
#endif
