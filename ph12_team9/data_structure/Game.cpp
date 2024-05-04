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
    killed_ES = 0, killed_ET = 0, killed_EG = 0, killed_AS = 0, killed_AD = 0, killed_AM = 0, killed_HU = 0, E_Df_total = 0, E_Dd_total = 0, E_Db_total = 0, A_Df_total = 0, A_Dd_total = 0, A_Db_total = 0;
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
    if (check_winner())
    {
        outfile << "//////////////////////////////////////////////////Earth Army////////////////////////////////////////////////////" << endl;
        outfile << "Total Earth soldier: " << random_generator->getES_total() << endl;
        outfile << "Total Earth tank: " << random_generator->getET_total() << endl; 
        outfile << "Total Earth gunnery: " << random_generator->getEG_total() << endl;
        outfile << "Total Earth HealUnits: " << random_generator->getHU_total() << endl;
        outfile << "Total Earth Healed Units: " << get_numOfHealedUnits() << endl;
        if (random_generator->getES_total() != 0)
            outfile << "percentage destructed Earth soldier: " << ((float)killed_ES / (random_generator->getES_total())) * 100 << "%" << endl;
        else
            outfile << "there is no Earth soldiers generated" << endl;
        if (random_generator->getET_total() != 0)
        outfile << "percentage destructed Earth tank: " << ((float)killed_ET / random_generator->getET_total()) * 100 << "%" << endl;
        else
            outfile << "percentage destructed Earth tank: there is no Earth soldiers generated" << endl;
        if (random_generator->getEG_total() != 0)
        outfile << "percentage destructed Earth gunnery: " << ((float)killed_EG / random_generator->getEG_total()) * 100 << "%" << endl;
        else
            outfile << "percentage destructed Earth gunnery: there is no Earth gunnery generated" << endl;
        if (random_generator->getHU_total() != 0)
        outfile << "percentage destructed Earth HealUnits: " << (killed_HU / random_generator->getHU_total()) * 100 << "%" << endl;
        else
            outfile << "percentage destructed Earth HealUnits::there is no Earth HealUnits generated" << endl;
        if (random_generator->getES_total()+ random_generator->getEG_total()+ random_generator->getHU_total()+ random_generator->getET_total() != 0)
        outfile << "percentage healed Earth Units: " << (float)get_numOfHealedUnits() / (random_generator->getES_total() + random_generator->getET_total() + random_generator->getEG_total()) * 100 << "%" << endl;
        else
            outfile << "percentage healed Earth Units: there is no healed Earth Units " << endl;
        if (random_generator->getES_total() + random_generator->getEG_total() + random_generator->getHU_total() + random_generator->getET_total() != 0)
        outfile << "percentage destructed Earth Army :" << (((float)killed_ES + killed_ET + killed_EG + killed_HU) / (random_generator->getES_total() + random_generator->getET_total() + random_generator->getEG_total() + random_generator->getHU_total())) * 100 << "%" << endl;
        else
            outfile << "percentage destructed Earth Army :" << "there is no Earth unit  generated" << endl;
        if (random_generator->getES_total() + random_generator->getEG_total() + random_generator->getHU_total() + random_generator->getET_total() != 0)
        outfile << "Average of Df = " << (float)E_Df_total / (random_generator->getES_total() + random_generator->getET_total() + random_generator->getEG_total() + random_generator->getHU_total())  << "\n";
        else
            outfile << "Average of Df = " << "there is no Earth unit  generated" << endl;
        if (killed_ES + killed_ET + killed_EG + killed_HU != 0)
        outfile << "Average of Dd = " << E_Dd_total / (killed_ES + killed_ET + killed_EG + killed_HU)  << "\n";
        else
            outfile << "Average of Dd = " << "there is no Earth unit have been destructed" << endl;
        if (killed_ES + killed_ET + killed_EG + killed_HU != 0)
            outfile << "Average of Db = " << E_Db_total / (killed_ES + killed_ET + killed_EG + killed_HU)  << "\n";
        else
            outfile << "Average of Db = " << "there is no Earth unit have been destructed" << endl;
        if (E_Db_total != 0)
            outfile << "Df/Db = " << (float)E_Df_total / E_Db_total * 100 << "%\n";
        else
            outfile << "Df/Db = " << "there is no Earth unit have been destructed" << endl;
        if (E_Db_total != 0)
             outfile << "Dd/Db = " << (float)E_Dd_total / E_Db_total * 100 << "%\n";
        else
            outfile << "Dd/Db = " << "there is no Earth unit have been destructed" << endl;
        outfile << "//////////////////////////////////////////////////Alien Army////////////////////////////////////////////////////" << endl;
        outfile << "Total Alien soldiers: " << random_generator->getAS_total() << endl;
        outfile << "Total Alien monsters: " << random_generator->getAM_total() << endl;
        outfile << "Total Alien drones: " << random_generator->getAD_total() << endl;
        outfile << "percentage destructed Alien soldiers: " << ((float)killed_AS / random_generator->getAS_total()) * 100 << "%" << endl;
        outfile << "percentage destructed Alien monsters: " << ((float)killed_AM / random_generator->getAM_total()) * 100 << "%" << endl;
        outfile << "percentage destructed Alien drones: " << ((float)killed_AD / random_generator->getAD_total()) * 100 << "%" << endl;
        outfile << "percentage destructed Alien Army :" << ((float)(killed_AS + killed_AM + killed_AD) / (random_generator->getAS_total() + random_generator->getAM_total() + random_generator->getAD_total())) * 100 << "%" << endl;
        outfile << "Average of Df = " << (float)A_Df_total / (killed_AS + killed_AM + killed_AD)  << "\n";
        outfile << "Average of Dd = " << (float)A_Dd_total / (killed_AS + killed_AM + killed_AD)  << "\n";
        outfile << "Average of Db = " << (float)A_Db_total / (killed_AS + killed_AM + killed_AD)  << "\n";
        outfile << "Df/Db = " << (float)A_Df_total / A_Db_total * 100 << "%\n";
        outfile << "Dd/Db = " << (float)A_Dd_total / A_Db_total * 100 << "%\n";
        if (silentMode)
        {
            cout << "the output file has been generated" << endl;
        }
    }
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
    case (earth_soldier):
        killed_ES++;
        E_Dd_total += unit->get_destruction_delay();
        E_Db_total += unit->get_battle_time();
        E_Df_total += unit->get_first_attack_delay();
        break;
    case(Tank):
        killed_ET++;
        E_Dd_total += unit->get_destruction_delay();
        E_Db_total += unit->get_battle_time();
        E_Df_total += unit->get_first_attack_delay();
        break;
    case(gunnery):
        killed_EG++;
        E_Dd_total += unit->get_destruction_delay();
        E_Db_total += unit->get_battle_time();
        E_Df_total += unit->get_first_attack_delay();
        break;
    case(Heal_soldier):
        killed_HU++;
        E_Dd_total += unit->get_destruction_delay();
        E_Db_total += unit->get_battle_time();
        E_Df_total += unit->get_first_attack_delay();
        break;
    case(alien_soldier):
        killed_AS++;
        A_Dd_total += unit->get_destruction_delay();
        A_Db_total += unit->get_battle_time();
        A_Df_total += unit->get_first_attack_delay();
        break;
    case(monster):
        killed_AM++;
        A_Dd_total += unit->get_destruction_delay();
        A_Db_total += unit->get_battle_time();
        A_Df_total += unit->get_first_attack_delay();
        break;
    case(drone):
        killed_AD++;
        A_Dd_total += unit->get_destruction_delay();
        A_Db_total += unit->get_battle_time();
        A_Df_total += unit->get_first_attack_delay();
        break;
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
    
}

bool Game::check_winner()
{
    if (current_time >= 40)
    {
        if (aliens->get_count() == 0 && humans->get_count() != 0)
        {
            if(!getSilentMode())
                cout << "Yeah!!Finally,We won!" << endl;
            return true;
        }
        else if (aliens->get_count() != 0 && humans->get_count() == 0)
        {
            if (!getSilentMode())
                cout << "We lost !!!!!!!!!" << endl;
                return true;
        }
        else if (aliens->get_count() == 0 && humans->get_count() == 0)
        {
            if (!getSilentMode())
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



