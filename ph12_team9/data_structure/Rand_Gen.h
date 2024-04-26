#pragma once
#ifndef RAN_GEN 
#define RAN_GEN
#include"AlienArmy.h"
#include"EarthArmy.h"
class Rand_Gen
{
private:
	int id_earth,id_alien;
	int N, ES, ET, EG, AS, AD, AM,Prop;
	int E_Cap0, E_Cap1, E_Pow0, E_Pow1, E_Health0, E_Health1;
	int A_Cap0, A_Cap1, A_Pow0, A_Pow1, A_Health0, A_Health1;
	Game* game_ptr;

public:
	Rand_Gen(Game* game);
	void setN(int x);
	void setES(int x);
	void setET(int x);
	void setEG(int x);
	void setAS(int x);
	void setAD(int x);
	void setAM(int x);
	void setProp(int x);
	void E_Cap(int x0,int x1);
	void E_Pow(int x0,int x1);
	void E_Health(int x0,int x1);
	void A_Cap(int x0,int x1);
	void A_Pow(int x0,int x1);
	void A_Health(int x0,int x1);
	int get_E_Pow0();
	int get_E_Pow1();
	armyUnit* generate_earth_unit(int join_time);
	armyUnit* generate_alien_unit(int join_time);
	//int find_in_queue(LinkedQueue<int> queue, int index);
};
#endif
