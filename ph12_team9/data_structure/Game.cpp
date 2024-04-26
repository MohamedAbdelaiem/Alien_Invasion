using namespace std;
#include<iostream>
#include "Game.h"
#include "time.h"
#include <conio.h>
#include<random>
Game::Game(string fileName)//initializes the system
{
	killed_list = new LinkedQueue<armyUnit*>;
	aliens = new AlienArmy;
	humans = new EarthArmy;
	random_generator = new Rand_Gen(this);
    UML = new priQueue<armyUnit*>;
	current_time = 0;
    loadFromInput(fileName);
}

void Game::attack()
{
    cout << "===================Units fighting at current step===============================\n";
    humans->attack();
    aliens->attack();
}

void Game::print_lists()//print all lists
{
	humans->print();
	cout << endl << endl;
	aliens->print();
	cout << endl << endl;
    cout << "==================Killed / Distructed List ================================\n";
    cout << killed_list->get_count() << " Units ";
    killed_list->print_list();
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

void Game::test()
{    
    for (int i = 0; i < 50; i++)
    {
        int x;
        increament_time();
        generate();
        cout << "\n\nTimeStep [" << get_current_time() << "]\n";
        cout << "before\n";
        print_lists();
        cout << "-------------------------------\n";
        cout << "after\n";

        //x = rand() % 100 + 1;
        x = 69;
        cout << "X = " << x << endl;
        if (x < 10)
        {
            armyUnit* ES = new earthSoldier;
            armyUnit* E = ES;
            humans->deleteUnit(ES);
            delete E;
            if(ES) humans->addUnit(ES);
        }
        else if (x < 20)
        {
            armyUnit* ES = new tank;
            armyUnit* E = ES;

            humans->deleteUnit(ES);
            delete E;
            if (ES)
            {

                ES->set_destroyed_time(current_time);
                ES->set_battle_time();
                killed_list->enqueue(ES);
            }
        }
        else if (x < 30)
        {
            armyUnit* ES = new Gunnery;
            armyUnit* E = ES;
            humans->deleteUnit(ES);
            if (ES)
            {
                ES->setHealth(ES->getHealth() / 2);
                humans->addUnit(ES);
            }
        }
        else if (x < 40)
        {
            int random_haelth;
            LinkedQueue<armyUnit*>temp_list;
            armyUnit* ES1 = new AllienSoldier;
            armyUnit* ES2 = new AllienSoldier;
            armyUnit* ES3 = new AllienSoldier;
            armyUnit* ES4 = new AllienSoldier;
            armyUnit* ES5 = new AllienSoldier;
            armyUnit* E1 = ES1;
            aliens->deleteUnit(ES1);
            delete E1;
            E1 = ES2;

            aliens->deleteUnit(ES2);
            delete E1;
            E1 = ES3;

            aliens->deleteUnit(ES3);
            delete E1;
            E1 = ES4;

            aliens->deleteUnit(ES4);
            delete E1;
            E1 = ES5;

            aliens->deleteUnit(ES5);
            delete E1;
            if (ES1)
            {
                temp_list.enqueue(ES1);
                random_haelth = rand() % (random_generator->get_E_Pow1() - random_generator->get_E_Pow0() + 1) + random_generator->get_E_Pow0();
                ES1->setHealth(ES1->getHealth() - random_haelth);
                
            }

            if (ES2)
            {
                temp_list.enqueue(ES2);
                random_haelth = rand() % (random_generator->get_E_Pow1() - random_generator->get_E_Pow0() + 1) + random_generator->get_E_Pow0();
                ES2->setHealth(ES2->getHealth() - random_haelth);
               
            }
            if (ES3)
            {
                temp_list.enqueue(ES3);
                random_haelth = rand() % (random_generator->get_E_Pow1() - random_generator->get_E_Pow0() + 1) + random_generator->get_E_Pow0();
                ES3->setHealth(ES3->getHealth() - random_haelth);
                
            }
            if (ES4)
            {
                temp_list.enqueue(ES4);
                random_haelth = rand() % (random_generator->get_E_Pow1() - random_generator->get_E_Pow0() + 1) + random_generator->get_E_Pow0();
                ES4->setHealth(ES4->getHealth() - random_haelth);
                
            }
            if (ES5)
            {
                temp_list.enqueue(ES5);
                random_haelth = rand() % (random_generator->get_E_Pow1() - random_generator->get_E_Pow0() + 1) + random_generator->get_E_Pow0();

                ES5->setHealth(ES5->getHealth() - random_haelth);
            }
            cout << "******************\t\t temp list is \t\t**********************" << endl;
            cout << temp_list.get_count() << " Units ";
            temp_list.print_list();
            while (!temp_list.isEmpty())
            {
                temp_list.dequeue(E1);
                if (E1->getHealth() == 0)
                {
                    killed_list->enqueue(E1);
                }
                else
                {
                    aliens->addUnit(E1);
                }
            }
        }
        else if (x < 50)
        {
            armyUnit* ES1 = new monsters;
            armyUnit* ES2 = new monsters;
            armyUnit* ES3 = new monsters;
            armyUnit* ES4 = new monsters;
            armyUnit* ES5 = new monsters;
            armyUnit* E = ES1;
            aliens->deleteUnit(ES1);
            delete E;
            E = ES2;
            aliens->deleteUnit(ES2);
            delete E;
            E = ES3;
            aliens->deleteUnit(ES3);
            delete E;
            E = ES4;
            aliens->deleteUnit(ES4);
            delete E;
            E = ES5;
            aliens->deleteUnit(ES5);
            delete E;

            if (ES1)
                aliens->addUnit(ES1);
            if (ES2)
                aliens->addUnit(ES2);
            if (ES3)
                aliens->addUnit(ES3);
            if (ES4)
                aliens->addUnit(ES4);
            if (ES5)
                aliens->addUnit(ES5);

        }
        else if (x < 60)
        {
            armyUnit* ES1 = new Drones;
            armyUnit* ES2 = new Drones;
            armyUnit* ES3 = new Drones;
            armyUnit* ES4 = new Drones;
            armyUnit* ES5 = new Drones;
            armyUnit* ES6 = new Drones;
            armyUnit* E1;
            armyUnit* E2;
            E1 = ES1;
            E2 = ES2;
            aliens->delete_two_drones(ES1, ES2);
            delete E1, E2;
            E1 = ES3;
            E2 = ES4;
            aliens->delete_two_drones(ES3, ES4);
            delete E1, E2;
            E1 = ES5;
            E2 = ES6;
            aliens->delete_two_drones(ES5, ES6);
            delete E1, E2;
            if (ES1)
            {
                ES1->set_destroyed_time(current_time);
                ES1->set_battle_time();
                killed_list->enqueue(ES1);
            }
            if (ES2)
            {
                ES2->set_destroyed_time(current_time);
                ES2->set_battle_time();
                killed_list->enqueue(ES2);
            }
            if (ES3)
            {
                ES3->set_destroyed_time(current_time);
                ES3->set_battle_time();
                killed_list->enqueue(ES3);
            }
            if (ES4)
            {
                ES4->set_destroyed_time(current_time);
                ES4->set_battle_time();
                killed_list->enqueue(ES4);
            }
            if (ES5) 
            {
                ES5->set_destroyed_time(current_time);
                ES5->set_battle_time();
                killed_list->enqueue(ES5);
            }
            if (ES6)
            {
                ES6->set_destroyed_time(current_time);
                ES6->set_battle_time();
                killed_list->enqueue(ES6);
            }
            if (!(ES1 && ES2 && ES3 && ES4 && ES5 && ES6) )
            {
                ES6 = new Drones;
                E1 = ES6;
                aliens->deleteUnit(ES6);
                if (ES6)
                {
                    ES6->set_destroyed_time(current_time);
                    ES6->set_battle_time();
                    killed_list->enqueue(ES6);
                }
                delete E1;
            }
        }
        else 
        {
            attack();
        }
        print_lists();
        //cout << "***********\t\t\t*********************\t\t\t\t***************************\n";
        cout << "***********\t\tpress enter to move to the next step\t\t******************\n";
        while (_getch() != 13) {};

    }
    cout << "The test code has been ended" << endl;
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
        else if (i == 5) random_generator->setAS(number);
        else if (i == 6) random_generator->setAM(number);
        else if (i == 7) random_generator->setAD(number);

        else if (i == 8)
        {
            int x0 = number;
            file >> number;
            if (number < 0) number = abs(number);
            i++;
            random_generator->E_Pow(x0, number);

        }
        else if (i == 10)
        {
            int x0 = number;
            file >> number;
            if (number < 0) number = abs(number);
            i++;
            random_generator->E_Health(x0, number);

        }
        else if (i == 12)
        {
            int x0 = number;
            file >> number;
            if (number < 0) number = abs(number);
            i++;
            random_generator->E_Cap(x0, number);

        }
        else if (i == 14)
        {
            int x0 = number;
            file >> number;
            if (number < 0) number = abs(number);
            i++;
            random_generator->A_Pow(x0, number);

        }
        else if (i == 16)
        {
            int x0 = number;
            file >> number;
            if (number < 0) number = abs(number);
            i++;
            random_generator->A_Health(x0, number);

        }
        else if (i == 18)
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
    killed_list->enqueue(unit);
}

AlienArmy* Game::get_aliens_pointer()
{
    return aliens;
}

EarthArmy* Game::get_humans_pointer()
{
    return humans;
}


Game::~Game()
{
    armyUnit* aa;
    int i;
    while (killed_list->dequeue(aa)) if (aa) delete aa;
    while (UML->dequeue(aa,i))  if (aa)delete aa;
	delete aliens, humans, random_generator,killed_list,UML;
}



