using namespace std;
#include<iostream>
#include "Game.h"
#include <conio.h>
#include<random>
Game::Game(string fileName,bool silentMode,string outfile)//initializes the system
{
    this->silentMode = silentMode;
	killed_list = new LinkedQueue<armyUnit*>;
	aliens = new AlienArmy;
	humans = new EarthArmy;
    allyArmy = new AllyArmy(this);
	random_generator = new Rand_Gen(this);
    UML = new priQueue<armyUnit*>;
	current_time = 1;
    numOfHealedUnits = 0;
    numOfInfectedSoldiers = 0;
    infected_in_uml = 0;

    loadFromInput(fileName);
    generate_output_file(outfile);
    SU_Helping = false;
    srand(time(0));
    killed_ES = 0, killed_ET = 0, killed_EG = 0, killed_AS = 0, killed_AD = 0, killed_AM = 0, killed_HU = 0,killed_SU = 0, E_Df_total = 0, E_Dd_total = 0, E_Db_total = 0, A_Df_total = 0, A_Dd_total = 0, A_Db_total = 0, total_infected_soldiers=0, S_Dd_total=0, S_Db_total=0, S_Df_total=0;
}

bool Game::attack()
{
    if(!this->silentMode)
    cout << "==================== Units fighting at current step ====================\n";
    bool humansAttack = humans->attack();      //--> make the earth army attack the alien army
    bool allyAttack = false;
    if (SU_Helping)
    {
        allyAttack = allyArmy->attack();     //--> make the ally army attack the alien army if the earth need to healp
    }
    bool aliensAttack = aliens->attack();   //--> make the alien army attack the earth army
    return(humansAttack || aliensAttack || allyAttack);    //--> return true if any of the armies attack successfully
}

void Game::print_lists() const//print all lists
{
    cout << "Current Timestep " << this->current_time << endl;
    cout << "==================== Earth Army Alive Units ====================\n";
	humans->print();
	cout << endl << endl;
    cout << "==================== Ally Army Alive Units ====================\n";
    allyArmy->print();
	cout << endl << endl;
    cout << "==================== Allien Army Alive Units ====================\n";
	aliens->print();
	cout << endl << endl;
   
}

void Game::generate()//generate alien and earth units
{
    
    
    int a = rand() % 100 + 1;
    if (a <= Prop)
    {
        for (int j = 0; j < N; j++)
        {
            armyUnit* a = random_generator->generate_earth_unit( current_time);
            if (a)
            {
                humans->addUnit(a);
            }
            
        }
    }
    a = rand() % 100 + 1;
    if (a <= Prop)
    {
        for (int j = 0; j < N; j++)
        {
           armyUnit*b= random_generator->generate_alien_unit(current_time);
           if (b)
               aliens->addUnit(b);
        }
    }
    if (SU_Helping)
    {

            for (int j = 0; j < numGen_SU; j++)
            {
                saverUnit* b = random_generator->generate_SU(current_time);
                if (b)
                    allyArmy->addUnit(b);

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

int Game::get_numOfHealedUnits() const
{
    return this->numOfHealedUnits;
}

bool Game::getSilentMode() const
{
    return this->silentMode;
}


void Game::simulate()
{
    while (true)
    {
        bool check_draw = false;
        if (random_generator->id_earth_total() != 1000 || random_generator->id_alien_total() != 3000||random_generator->id_ally_total()!=4250)
        {
            this->generate();
        }
        if (random_generator->id_earth_total() == 1000 && random_generator->id_alien_total() == 3000&&random_generator->id_ally_total() == 4250)
        {
            if (!silentMode)
            {
                cout << "The generation has reached the maximum number of ids for  earth , aliens and ally armies" << endl;
            }
        }
        this->RandomIfection();
        if (!silentMode)
            this->print_lists();
        
        check_draw = this->attack();
        
        this->checkSuHelping();   //--> check if the Earth Army need to help or not

        if (!silentMode)
        {
            cout << "==================== UML ====================\n\n";
            cout << UML->getCount() << " Units ";
            UML->print_list();
            cout << "==================== Killed / Distructed List ====================\n\n";
            cout << killed_list->get_count() << " Units ";
            killed_list->print_list();
            
            
        }
        if (!silentMode)
        {
            cout << "======================infected_units precntage after attack==================\n";
            cout << "Number of infected soldiers is: " << numOfInfectedSoldiers << endl;
            if (random_generator->getES_total() - killed_ES != 0)
                cout << "The precntage of infected soldiers is " << float(numOfInfectedSoldiers) / (random_generator->getES_total() - killed_ES) * 100 << " %\n";
            else
                cout << "The precntage of infected soldiers is " << "There isn't any earth soldier in the battle" << "\n\n\n";
            cout << "***********\t\tpress enter to move to the next step or s to switch to silent mode directly \t\t***********\n\n\n";
            char c = _getch();
            while (c != 13)
            {
                if (tolower(c) == 's')
                {
                    silentMode = true;
                    break;
                }
                c= _getch();
            };
        }
        if (check_winner(check_draw))
        {
            if (aliens->get_count() != 0 && humans->get_count() == 0)
            {
                this->kill_UML();
                this->checkSuHelping();
            }
            outfile << "//////////////////////////////////////////////////Earth Army////////////////////////////////////////////////////" << endl;
            outfile << "Total Earth soldier: " << random_generator->getES_total() << endl;
            outfile << "Total Earth tank: " << random_generator->getET_total() << endl;
            outfile << "Total Earth gunnery: " << random_generator->getEG_total() << endl;
            outfile << "Total Earth HealUnits: " << random_generator->getHU_total() << endl;
            outfile << "Total Earth Healed Units: " << get_numOfHealedUnits() << endl;
            outfile << "Total Infected Earth Soldiers: " << numOfInfectedSoldiers << endl;
            outfile << "Total Units Still in The UML is: " << UML->getCount() << endl;
            if (random_generator->getES_total() != 0)
                outfile << "percentage destructed Earth soldier: " << ((float)killed_ES / (random_generator->getES_total())) * 100 << "%" << endl;
            else
                outfile << "percentage destructed Earth soldier: " << "there is no Earth soldiers generated" << endl;
            if (random_generator->getES_total() != 0)
                outfile << "percentage Infected Earth soldier: " << ((float)numOfInfectedSoldiers / (random_generator->getES_total())) * 100 << "%" << endl;
            else
                outfile << "percentage destructed Earth soldier: " << "there is no Earth soldiers generated" << endl;
            if (random_generator->getET_total() != 0)
                outfile << "percentage destructed Earth tank: " << ((float)killed_ET / random_generator->getET_total()) * 100 << "%" << endl;
            else
                outfile << "percentage destructed Earth tank: there is no Earth Tanks generated" << endl;
            if (random_generator->getEG_total() != 0)
                outfile << "percentage destructed Earth gunnery: " << ((float)killed_EG / random_generator->getEG_total()) * 100 << "%" << endl;
            else
                outfile << "percentage destructed Earth gunnery: there is no Earth gunnery generated" << endl;
            if (random_generator->getHU_total() != 0)
                outfile << "percentage destructed Earth HealUnits: " << (killed_HU / random_generator->getHU_total()) * 100 << "%" << endl;
            else
                outfile << "percentage destructed Earth HealUnits::there is no Earth HealUnits generated" << endl;
            if (random_generator->getES_total() + random_generator->getEG_total() + random_generator->getHU_total() + random_generator->getET_total() != 0)
                outfile << "percentage healed Earth Units: " << (float)get_numOfHealedUnits() / (random_generator->getES_total() + random_generator->getET_total() + random_generator->getEG_total()) * 100 << "%" << endl;
            else
                outfile << "percentage healed Earth Units: there is no healed Earth Units " << endl;
            if (random_generator->getES_total() + random_generator->getEG_total() + random_generator->getHU_total() + random_generator->getET_total() != 0)
                outfile << "percentage destructed Earth Army :" << (((float)killed_ES + killed_ET + killed_EG + killed_HU) / (random_generator->getES_total() + random_generator->getET_total() + random_generator->getEG_total() + random_generator->getHU_total())) * 100 << "%" << endl;
            else
                outfile << "percentage destructed Earth Army :" << "there is no Earth unit  generated" << endl;
            if (random_generator->getES_total() + random_generator->getEG_total() + random_generator->getHU_total() + random_generator->getET_total() != 0)
                outfile << "Average of Df = " << (float)E_Df_total / (killed_ES + killed_ET + killed_EG + killed_HU) << "\n";
            else
                outfile << "Average of Df = " << "there is no Earth unit  generated" << endl;
            if (killed_ES + killed_ET + killed_EG + killed_HU != 0)
                outfile << "Average of Dd = " << (float)E_Dd_total / (killed_ES + killed_ET + killed_EG + killed_HU) << "\n";
            else
                outfile << "Average of Dd = " << "there is no Earth unit have been destructed" << endl;
            if (killed_ES + killed_ET + killed_EG + killed_HU != 0)
                outfile << "Average of Db = " << (float)E_Db_total / (killed_ES + killed_ET + killed_EG + killed_HU) << "\n";
            else
                outfile << "Average of Db = " << "there is no Earth unit have been destructed" << endl;
            if (E_Db_total != 0)
                outfile << "Df/Db = " << (float)E_Df_total / E_Db_total * 100 << "%\n";
            else
                outfile << "Df/Db = " << "there is no Earth unit have been destructed" << endl;
            if (E_Db_total != 0)
                outfile << "Dd/Db = " << (float)E_Dd_total / E_Db_total * 100 << "%\n";
            else
                outfile << "Dd/Db = " << "there is no Earth unit have been destructed" << endl<<endl;
            outfile<<"//////////////////////////////////////////////////Ally Army////////////////////////////////////////////////////" << endl;

            outfile << "Total Saver Units :" << random_generator->getSU_total() << endl;
            outfile << "Total destructed Saver Units: " << killed_SU << endl;
            if (random_generator->getSU_total())
            {
                outfile << "percentage destructed Earth Saver Units: " << float(killed_SU) / random_generator->getSU_total() * 100 << "%" << endl;
            }
            else  outfile << "percentage destructed Earth Saver Units: There are not any SU have been generated"<<endl;

            if (killed_SU != 0)
                outfile << "Average of Df = " << (float)S_Df_total / (killed_SU) << "\n";
            else
                outfile << "Average of Df = " << "there is no Saver unit  generated" << endl;
            if (killed_SU != 0)
                outfile << "Average of Dd = " << (float)S_Dd_total / (killed_SU) << "\n";
            else
                outfile << "Average of Dd = " << "there is no Saver unit have been destructed" << endl;
            if (killed_SU != 0)
                outfile << "Average of Db = " << (float)S_Db_total / (killed_SU) << "\n";
            else
                outfile << "Average of Db = " << "there is no Saver unit have been destructed" << endl;
            if (S_Db_total != 0)
                outfile << "Df/Db = " << (float)S_Df_total / S_Db_total * 100 << "%\n";
            else
                outfile << "Df/Db = " << "there is no Saver unit have been destructed" << endl;
            if (S_Db_total != 0)
                outfile << "Dd/Db = " << (float)S_Dd_total / S_Db_total * 100 << "%\n";
            else
                outfile << "Dd/Db = " << "there is no Saver unit have been destructed" << endl<<endl;
            outfile << "//////////////////////////////////////////////////Alien Army////////////////////////////////////////////////////" << endl;
            outfile << "Total Alien soldiers: " << random_generator->getAS_total() << endl;
            outfile << "Total Alien monsters: " << random_generator->getAM_total() << endl;
            outfile << "Total Alien drones: " << random_generator->getAD_total() << endl;
            if (random_generator->getAS_total() != 0)
                outfile << "percentage destructed Alien soldiers: " << ((float)killed_AS / random_generator->getAS_total()) * 100 << "%" << endl;
            else
                outfile << "percentage destructed Alien soldiers: there is no alien soldiers have been generated generated" << endl;
            if (random_generator->getAM_total() != 0)
                outfile << "percentage destructed Alien monsters: " << ((float)killed_AM / random_generator->getAM_total()) * 100 << "%" << endl;
            else
                outfile << "percentage destructed Alien monsters: there is no alien monsters generated" << endl;
            if (random_generator->getAD_total() != 0)
                outfile << "percentage destructed Alien drones: " << ((float)killed_AD / random_generator->getAD_total()) * 100 << "%" << endl;
            else
                outfile << "percentage destructed Alien drones: there is no alien drones generated" << endl;
            if (random_generator->getAS_total() + random_generator->getAM_total() + random_generator->getAD_total() != 0)
                outfile << "percentage destructed Alien Army :" << ((float)(killed_AS + killed_AM + killed_AD) / (random_generator->getAS_total() + random_generator->getAM_total() + random_generator->getAD_total())) * 100 << "%" << endl;
            else
                outfile << "percentage destructed Alien Army :" << "there is no Earth unit  generated" << endl;
            if (killed_AS + killed_AM + killed_AD != 0)
                outfile << "Average of Df = " << (float)A_Df_total / (killed_AS + killed_AM + killed_AD) << "\n";
            else
                outfile << "Average of Df : there is no alien unit have been killed" << endl;
            if (killed_AS + killed_AM + killed_AD != 0)
                outfile << "Average of Dd = " << (float)A_Dd_total / (killed_AS + killed_AM + killed_AD) << "\n";
            else
                outfile << "Average of Dd : there is no alien unit have been killed" << endl;
            if (killed_AS + killed_AM + killed_AD != 0)
                outfile << "Average of Db = " << (float)A_Db_total / (killed_AS + killed_AM + killed_AD) << "\n";
            else
                outfile << "Average of Db : there is no alien unit have been killed" << endl;
            if (A_Db_total != 0)
                outfile << "Df/Db = " << (float)A_Df_total / A_Db_total * 100 << "%\n";
            else
                outfile << "Df/Db = " << "there is no Alien unit have been destructed" << endl;
            if (A_Db_total != 0)
                outfile << "Dd/Db = " << (float)A_Dd_total / A_Db_total * 100 << "%\n";
            else
                outfile << "Dd/Db = " << "there is no Alien unit have been destructed" << endl;
            if (silentMode)
            {
                cout << "SilentMode:" << endl;
                cout << "the output file has been generated" << endl;
            }
            outfile << "//////////////////////////////////////////////////Battle informations////////////////////////////////////////////////////" << endl;

            if (aliens->get_count() == 0 && humans->get_count() != 0)
            {
                if (!getSilentMode())
                {
                    cout << "Yeah!!Finally,We won!" << endl;
                    PlaySound(TEXT("winning"), NULL, SND_FILENAME | SND_SYNC);
                }
                outfile << "\n Yeah!!Finally,We won!\n";

            }
            else if (aliens->get_count() != 0 && humans->get_count() == 0)
            {
                if (!getSilentMode())
                {
                    cout << "We lost !!!!!!!!!" << endl;
                    PlaySound(TEXT("lose.wav"), NULL, SND_FILENAME | SND_SYNC);
                }
                outfile << "We lost !!!!!!!!!" << endl;
            }
            else if (aliens->get_count() == 0 && humans->get_count() == 0)
            {
                if (!getSilentMode())
                    cout << " The fight ended with Draw" << endl;
                outfile << "The fight has been ended with Draw" << endl;
            }
            else if (!check_draw)
            {
                if (!getSilentMode())
                    cout << " The fight ended with Draw" << endl;
                outfile << "The fight has been ended with Draw" << endl;
            }
            outfile << "Final Time Step :" << current_time << endl;
            if (random_generator->id_earth_total() == 1000 && random_generator->id_alien_total() == 3000 && random_generator->id_ally_total() == 4250)
            {
                if (silentMode)
                {
                    outfile << "The generation has reached the maximum number of ids for  earth , aliens and ally armies" << endl;
                }
            }
            break;
        }
    this->current_time++;
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
        else if (i == 21)
        {
            random_generator->setInfectionProb(number);
        }
        else if (i == 22)
        {
            this->treshold= number;
        }
        else if (i == 23)
        {
            numGen_SU = number;
        }
        else if (i == 24)
        {
            int x0 = number;
            file >> number;
            if (number < 0) number = abs(number);
            i++;
            random_generator->SU_pow(x0, number);
        }
        else if (i == 26)
        {
            int x0 = number;
            file >> number;
            if (number < 0) number = abs(number);
            i++;
            random_generator->SU_Health(x0, number);
        }
        else if (i == 28)
        {
            int x0 = number;
            file >> number;
            if (number < 0) number = abs(number);
            i++;
            random_generator->SU_cap(x0, number);
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
        if (unit->get_infection())
        {
            decrease_numOfInfectedSoldiers();
        }
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
    case(saver_unit):
        killed_SU++;
        S_Dd_total += unit->get_destruction_delay();
        S_Db_total += unit->get_battle_time();
        S_Df_total += unit->get_first_attack_delay();
        break;
    default:
        break;
    }
    killed_list->enqueue(unit);
}

void Game::add_to_UML(armyUnit* unit, int priority)
{
    if (unit)
    {
        UML->enqueue(unit, priority);     //--> add a unit to UML
        if (unit->get_infection())
            infected_in_uml++;       //--> increase number of infected soldiers if the unit was infected
    }
}

void Game::increase_numOfInfectedSoldiers(int x )
{
    numOfInfectedSoldiers += x;
}

void Game::decrease_numOfInfectedSoldiers()
{
    numOfInfectedSoldiers--;
}

void Game::decrease_numOfInfectedSoldiersInUML()
{
    infected_in_uml--;
}

void Game::RandomIfection()
{
    int count = humans->RandomInfection(numOfInfectedSoldiers-infected_in_uml);
    increase_numOfInfectedSoldiers(count);
    increase_total_number_of_infected(count);
}



priQueue<armyUnit*>* Game::get_UML() const
{
    return this->UML;
}

AlienArmy* Game::get_aliens_pointer() const
{
    return aliens;
}

EarthArmy* Game::get_humans_pointer() const
{
    return humans;
}

AllyArmy* Game::get_Ally_pointer() const
{
    return allyArmy;
}

bool Game::EarthArmy_Need_TO_Help() const
{
    //int total_alive_earthArmy_units = humans->get_count() + UML->getCount();

    int total_alive_earthArmy_units = (random_generator->getES_total() - killed_ES);    //--> total earth soldiers
    int total_infected_units = this->numOfInfectedSoldiers;    //--> total infected soldiers
    return (total_alive_earthArmy_units!=0 && (total_infected_units / float(total_alive_earthArmy_units)*100 >= treshold));   //--> if the percentage of the infected to all soldiers reaches the treshold return treu

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

bool Game::check_winner(bool draw )
{
    if (current_time >= 40)
    {
        if (aliens->get_count() == 0 && humans->get_count() != 0)
        {
            return true;
        }
        else if (aliens->get_count() != 0 && humans->get_count() == 0)
        {
           
                return true;
        }
        else if (aliens->get_count() == 0 && humans->get_count() == 0)
        {
            
            return true;
        }
        else if(!draw)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    return false;
}

void Game::checkSuHelping()
{
    if (EarthArmy_Need_TO_Help())        //--> if the earth army need to help
    {
         SU_Helping = true;            
    }
    else if (numOfInfectedSoldiers == 0)     //--> if we reached zero in number of infected soldiers
    {
        if (SU_Helping)          //--> check if the SU was helping before then destroy all the SUs if true
        {
            allyArmy->destroyAll();
            SU_Helping = false;
        }
    }
}

void Game::increase_total_number_of_infected(int count)
{
    total_infected_soldiers += count;
}

void Game::kill_UML()
{
    armyUnit* unit; int x;
    while (UML->dequeue(unit, x))
    {
        if (unit->get_infection())
            decrease_numOfInfectedSoldiersInUML();
        unit->setHealth(0);
        add_to_killed_list(unit);
    }

}


Game::~Game()
{
    armyUnit* aa;
    int i;
    while (killed_list->dequeue(aa)) if (aa) delete aa;
    while (UML->dequeue(aa,i))  if (aa)delete aa;

	delete aliens, humans, random_generator, killed_list, UML, allyArmy;
}



