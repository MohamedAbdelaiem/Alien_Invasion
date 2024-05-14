#pragma once
#ifndef GA_ME
#define GA_ME
#include<iostream>
#include<fstream>
#include <Windows.h>
#include<mmsystem.h>
#pragma comment(lib, "Winmm.lib") 
#include"AlienArmy.h"
#include"EarthArmy.h"
#include "Ally_Army.h"
#include"Rand_Gen.h"
using namespace std;
class Game
{
private:
	LinkedQueue<armyUnit*>*killed_list;
	priQueue<armyUnit*>* UML;
	AlienArmy* aliens;
	EarthArmy* humans;
	AllyArmy* allyArmy;
	Rand_Gen*random_generator;
	ofstream outfile;
	int current_time;
	int N, Prop,killed_ES, killed_ET, killed_EG, killed_AS, killed_AD, killed_AM, killed_HU,killed_SU,E_Df_total, E_Dd_total, E_Db_total,  A_Df_total, A_Dd_total, A_Db_total,total_infected_soldiers;
	int numOfHealedUnits,numOfInfectedSoldiers, infected_in_uml, S_Dd_total, S_Db_total, S_Df_total;
	bool silentMode;
	int treshold;
	int numGen_SU;
	bool SU_Helping;
	
public:
	Game(string fileName ,bool silentMode,string out_file);
	bool attack();	
	void print_lists() const;
	void generate();
	void increament_time();
	int  get_current_time(); 
	void setSilentMode(bool mode);  //--> set the silent mode
	void incr_numOfHealedUnits();  //--> increament the num of healed units
	int get_numOfHealedUnits() const;  //--> get the number of healed units
	bool  getSilentMode() const;   //--> check the mode we play in it
	void simulate();
	bool loadFromInput(string fileName);
	void add_to_killed_list(armyUnit* unit); //--> add a unit to killed list
	void add_to_UML(armyUnit* unit, int priority);   //--> add a unit to UML
	void increase_numOfInfectedSoldiers(int x = 1);
	void decrease_numOfInfectedSoldiers();
	void decrease_numOfInfectedSoldiersInUML();
	void RandomIfection();
	priQueue<armyUnit*>* get_UML() const;	//--> get pointer to UML
	AlienArmy* get_aliens_pointer() const;	//--> get pointer to Alien Army
	EarthArmy* get_humans_pointer() const;  //--> get pointer to earth Army
	AllyArmy* get_Ally_pointer() const;  //--> get pointer to Ally Army
	bool EarthArmy_Need_TO_Help() const;   //--> chaeck if the Earth Army need to help 
	void generate_output_file(string filename);
	void add_to_file(armyUnit* unit);
	bool check_winner(bool flag=true);
	void checkSuHelping();    //--> chaeck if the Earth Army need to help and edit the boolen (SU_Healping) 
	void increase_total_number_of_infected(int count);
	void kill_UML(); //--> kill all unit in UML
	~Game();



};
#endif

