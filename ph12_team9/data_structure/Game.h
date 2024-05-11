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
#include"Rand_Gen.h"
using namespace std;
class Game
{
private:
	LinkedQueue<armyUnit*>*killed_list;
	priQueue<armyUnit*>* UML;
	AlienArmy* aliens;
	EarthArmy* humans;
	Rand_Gen*random_generator;
	ofstream outfile;
	int current_time;
	int N, Prop,killed_ES, killed_ET, killed_EG, killed_AS, killed_AD, killed_AM, killed_HU,E_Df_total, E_Dd_total, E_Db_total,  A_Df_total, A_Dd_total, A_Db_total;
	int numOfHealedUnits,numOfInfectedSoldiers, infected_in_uml;
	bool silentMode;
	
public:
	Game(string fileName ,bool silentMode,string out_file);
	bool attack();	
	void print_lists();
	void generate();
	void increament_time();
	int  get_current_time(); 
	void setSilentMode(bool mode); 
	void incr_numOfHealedUnits();
	int get_numOfHealedUnits();
	bool  getSilentMode(); 
	void simulate();
	bool loadFromInput(string fileName);
	void add_to_killed_list(armyUnit* unit);
	void add_to_UML(armyUnit* unit, int priority);
	void increase_numOfInfectedSoldiers(int x = 1);
	void decrease_numOfInfectedSoldiers();
	void decrease_numOfInfectedSoldiersInUML();
	void RandomIfection();
	priQueue<armyUnit*>* get_UML();
	AlienArmy* get_aliens_pointer();
	EarthArmy* get_humans_pointer();
	void generate_output_file(string filename);
	void add_to_file(armyUnit* unit);
	bool check_winner(bool flag=true);
	~Game();



};
#endif

