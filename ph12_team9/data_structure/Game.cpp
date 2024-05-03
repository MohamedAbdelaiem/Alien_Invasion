using namespace std;
#include<iostream>
#include "Game.h"
#include "time.h"
#include <conio.h>
#include<random>
Game::Game(string fileName,bool silentMode,string outfile)//initializes the system
{
    this->silentMode = silentMode;
	killed_list = new LinkedQueue<armyUnit*>;
	aliens = new AlienArmy;
	humans = new EarthArmy;
	random_generator = new Rand_Gen(this);
    UML = new priQueue<armyUnit*>;
	current_time = 1;
    numOfHealedUnits = 0;
    loadFromInput(fileName);
    generate_output_file(outfile);
}

void Game::attack()
{
    if(!this->silentMode)
    cout << "==================== Units fighting at current step ====================\n";
    humans->attack();
    aliens->attack();
}

void Game::print_lists()//print all lists
{
    cout << "Current Timestep " << this->current_time << endl;
    cout << "==================== Earth Army Alive Units ====================\n";
	humans->print();
	cout << endl << endl;
    cout << "==================== Allien Army Alive Units ====================\n";
	aliens->print();
	cout << endl << endl;
   
}

void Game::generate()//generate alien and earth units
{
    srand(time(0));
    int a = rand() % 100 + 1;
    if (a <= Prop)
    {
        for (int j = 0; j < N; j++)
        {
            armyUnit* a = random_generator->generate_earth_unit( current_time);
            humans->addUnit(a);
        }
    }
    a = rand() % 100 + 1;
    if (a <= Prop)
    {
        for (int j = 0; j < N; j++)
        {
            aliens->addUnit(random_generator->generate_alien_unit(current_time));
        }
    }
}

void Game::increament_time()
{
    current_time++;
}

int Game::get_current_time()
{
    return current_time;
}

void Game::setSilentMode(bool mode)
{
    this->silentMode = mode;
}

void Game::incr_numOfHealedUnits()
{
    this->numOfHealedUnits++;
}

int Game::get_numOfHealedUnits()
{
    return this->numOfHealedUnits;
}

bool Game::getSilentMode()
{
    return this->silentMode;
}


void Game::simulate()
{
    this->generate();
    if(!silentMode)
    this->print_lists();

    this->attack();
    if (!silentMode)
    {
        cout << "==================== UML ====================\n";
        cout << UML->getCount()<< " Units ";
        UML->print_list();
        cout << "==================== Killed / Distructed List ====================\n";
        cout << killed_list->get_count() << " Units ";
        killed_list->print_list();
        cout << "***********\t\tpress enter to move to the next step\t\t******************\n\n\n";
        while (_getch() != 13) {};
    }
    this->current_time++;
}

bool Game::loadFromInput(string fileName)
{

    ifstream file;
    file.open(fileName + ".txt");
    if (file.fail())
    {
        return false;
    }
    int number, i = 0;
    while (file >> number)
    {
        if (number < 0) number = abs(number);
        if (i == 0)
        {
            random_generator->setN(number);
            N = number;
        }
        else if (i == 1)
        {
            random_generator->setProp(number);
            Prop = number;
        }
        else if (i == 2) random_generator->setES(number);
        else if (i == 3) random_generator->setET(number);
        else if (i == 4) random_generator->setEG(number);
        else if (i == 5) random_generator->setHU(number);
        else if (i == 6) random_generator->setAS(number);
        else if (i == 7) random_generator->setAM(number);
        else if (i == 8) random_generator->setAD(number);

        else if (i == 9)
        {
            int x0 = number;
            file >> number;
            if (number < 0) number = abs(number);
            i++;
            random_generator->E_Pow(x0, number);

        }
        else if (i == 11)
        {
            int x0 = number;
            file >> number;
            if (number < 0) number = abs(number);
            i++;
            random_generator->E_Health(x0, number);

        }
        else if (i == 13)
        {
            int x0 = number;
            file >> number;
            if (number < 0) number = abs(number);
            i++;
            random_generator->E_Cap(x0, number);

        }
        else if (i == 15)
        {
            int x0 = number;
            file >> number;
            if (number < 0) number = abs(number);
            i++;
            random_generator->A_Pow(x0, number);

        }
        else if (i == 17)
        {
            int x0 = number;
            file >> number;
            if (number < 0) number = abs(number);
            i++;
            random_generator->A_Health(x0, number);

        }
        else if (i == 19)
        {
            int x0 = number;
            file >> number;
            if (number < 0) number = abs(number);
            i++;
            random_generator->A_Cap(x0, number);

        }

        i++;
    }
    file.close();
    return true;
}


void Game::add_to_killed_list(armyUnit* unit)
{
    unit->set_destroyed_time(current_time);
    unit->set_destruction_delay();
    unit->set_battle_time();
    add_to_file(unit);
    switch (unit->getUnitType())
    {
    earth_soldier:killed_ES++;
    Tank:killed_ET++;
    gunnery:killed_EG++;
    Heal_soldier:killed_HU++;
    alien_soldier:killed_AS++;
    monster:killed_AM++;
    drone:killed_AD++;
    default:
        break;
    }
    killed_list->enqueue(unit);
}

void Game::add_to_UML(armyUnit* unit, int priority)
{
    if(unit)
    UML->enqueue(unit, priority);
}

priQueue<armyUnit*>* Game::get_UML()
{
    return this->UML;
}

AlienArmy* Game::get_aliens_pointer()
{
    return aliens;
}

EarthArmy* Game::get_humans_pointer()
{
    return humans;
}

void Game::generate_output_file(string filename)
{
    outfile.open(filename+".txt");
    outfile << "Td\tID\tTj\tDf\tDd\tDb\t" << endl;
}

void Game::add_to_file(armyUnit* unit)
{
    outfile << unit->get_destroyed_time() << "\t" << unit->getID() << "\t" << unit->getJoinTime() << "\t" << unit->get_first_attack_delay() << "\t" << unit->get_destruction_delay() << "\t" << unit->get_battle_time() << endl;
    if (check_winner())
    {
        outfile<< "//////////////////////////////////////////////////Earth Army////////////////////////////////////////////////////" << endl;
        outfile << "Total Earth soldier: " << humans->ES_get_count() << endl;
        outfile << "Total Earth tank: " << humans->ET_get_count() << endl;
        outfile << "Total Earth gunnery: " << humans->EG_get_count() << endl;
        outfile << "Total Earth HealUnits: " << humans->HU_get_count() << endl;
        outfile << "percentage destructed Earth soldier: " << (killed_ES/ (humans->ES_get_count()))*100<<"%" << endl;
        outfile << "percentage destructed Earth tank: " << (killed_ET / humans->ET_get_count())*100 <<"%" << endl;
        outfile << "percentage destructed Earth gunnery: " << (killed_EG / humans->EG_get_count()) * 100 << "%" << endl;
        outfile << "percentage destructed Earth HealUnits: " << (killed_HU / humans->HU_get_count()) * 100 << "%" << endl;
        outfile << "percentage destructed Earth Army :" << ((killed_ES + killed_ET + killed_EG + killed_HU) / (humans->ES_get_count() + humans->ET_get_count() + humans->EG_get_count() + humans->HU_get_count())) * 100 << "%" << endl;

    }
}

bool Game::check_winner()
{
    if (current_time >= 40)
    {
        if (aliens->get_count() == 0 && humans->get_count() != 0)
        {
            cout << "Yeah!!Finally,We won!" << endl;
            return true;
        }
        else if (aliens->get_count() != 0 && humans->get_count() == 0)
        {
            cout << "We lost !!!!!!!!!" << endl;
            return true;
        }
        else if (aliens->get_count() == 0 && humans->get_count() == 0)
        {
            cout << " The fight ended with Draw" << endl;
        }
        else
        {
            return false;
        }
    }
    return false;
}


Game::~Game()
{
    armyUnit* aa;
    int i;
    while (killed_list->dequeue(aa)) if (aa) delete aa;
    while (UML->dequeue(aa,i))  if (aa)delete aa;

	delete aliens, humans, random_generator,killed_list,UML;
}



