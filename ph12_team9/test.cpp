// test.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include"data_structure/Game.h"
using namespace std;
int main()
{
	string fileName;
	bool ModeSilent;
	char mode='h';
	do {
		cout << "Which mode you want?\n";
		cout << "A) Silent\nB) Interactive\n";
		cin >> mode;
	} while (mode != 'A' && mode != 'a' && mode != 'b' && mode != 'B');
	if (mode == 'B' || mode == 'b')
	{
		ModeSilent = false;
	}
	else
	{
		ModeSilent = true;
	}
		cout << "Enter the file name: ";
		cin >> fileName;
		cout << endl;
		Game g1(fileName,ModeSilent);
		for (int i = 0; i < 50; i++)
			g1.simulate();
	return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
