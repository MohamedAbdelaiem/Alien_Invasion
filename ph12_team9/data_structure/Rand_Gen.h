#pragma once
#ifndef RAN_GEN 
#define RAN_GEN
#include"AlienArmy.h"
#include"EarthArmy.h"
#include "Ally_Army.h"
class Rand_Gen
{
private:
	Game* game_ptr;
	int id_earth,id_alien;
	int N, ES, ET, EG, AS, AD, AM,HU,Prop;
	int E_Cap0, E_Cap1, E_Pow0, E_Pow1, E_Health0, E_Health1;
	int A_Cap0, A_Cap1, A_Pow0, A_Pow1, A_Health0, A_Health1;
	int infection_prob;
	int AD_total;
	int AM_total;
	int AS_total;
	int ES_total;
	int ET_total;
	int EG_total;
	int HU_total;

	// for SU 
	int SU_cap0,SU_cap1,SU_pow0,SU_pow1,SU_Health0,SU_Health1;


public:
	Rand_Gen(Game* game);
	void setN(int x);     
	void setES(int x);
	void setET(int x);
	void setEG(int x);
	void setAS(int x);
	void setAD(int x);
	void setAM(int x);
	void setHU(int x);
	void setInfectionProb(int x);
	void setProp(int x);
	void E_Cap(int x0,int x1);  //--> set the ranges of the earth army capacity
	void E_Pow(int x0,int x1);  //--> set the ranges of the earth army powers
	void E_Health(int x0,int x1);	//--> set the ranges of the earth army Health
	void A_Cap(int x0,int x1);    //--> set the ranges of the alien army capacity
	void A_Pow(int x0,int x1);   //--> set the ranges of the alien army powers
	void A_Health(int x0,int x1);   //--> set the ranges of the alien army Health
	void SU_Health(int x0,int x1); //--> set the ranges of the ally army Health
	void SU_pow(int x0,int x1);	//--> set the ranges of the ally army powers
	void SU_cap(int x0,int x1);		//--> set the ranges of the ally army capacity
	int get_E_Pow0();   
	int get_E_Pow1();
	int getAD_total();
	int getAM_total();
	int getAS_total();
	int getES_total();
	int getET_total();
	int getEG_total();
	int getHU_total();
	int id_earth_total();
	int id_alien_total();
	armyUnit* generate_earth_unit(int join_time); //--> generate an earth unit
	armyUnit* generate_alien_unit(int join_time); //--> generate an alien unit
	saverUnit* generate_SU(int join_time);  //--> generate a saver unit
};
#endif
