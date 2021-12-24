/*******************************************************************************
* AUTHOR : Ethan Safai
* DATE   : 09/01/21
*******************************************************************************/
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

/*******************************************************************************
* This program reads in a list of names of files that the user would like to
* compile and manage using a Makefile and generates the Makefile for them in
* this directory. The user must then move (using a GUI or the mv command) the 
* Makefile that was output to this directory to their desired directory.
*
* CONDITIONS:
* 	The first file read MUST be the file including the program's main method
*******************************************************************************/

int main()
{
	int index = 0;        // index for vector
	bool exit = false;    // LCV for read
	string output;        // executable file name
	string file;          // source file name
	vector<string> files; // vector of file names
	ofstream outFile;     // output file for makefile

	// Read executable file name
	cout << "Enter output (executable) file name: ";
	getline(cin, output);

	// Read file names until user enters 'X'
	cout << "\n(First file must be the file with the main method)\n";
	do
	{
		if (index == 0)
			cout << "Enter main file name ('X' to stop):   ";
		else
			cout << "Enter header file name ('X' to stop): ";
		cin >> file;
		files.push_back(file);

		if (files[index++] == "X")
			exit = true;
	} while (!exit);
	// Remove 'X' from vector
	files.pop_back();

	outFile.open("Makefile");
	if (outFile.fail())
	{
		cout << "Failure to open output file!\n";
		return 1;
	}

	outFile << "CC = g++\n";
	outFile << "FLAGS = -std=c++17 -Wall -g\n";
	outFile << "OBJS = ";
	for (int i = 0; i < files.size(); i++)
		outFile << files[i] << ".o ";
	outFile << endl << endl;

	// All target
	outFile << "all: " << output << endl << endl;
	outFile << output << ": $(OBJS)\n";
	outFile << "\t$(CC) -o " << output << " $(FLAGS) $(OBJS)\n\n";

	// File with main individual target
	outFile << files[0] << ".o: " << files[0] << ".cpp\n";
	outFile << "\t$(CC) $(FLAGS) -c " << files[0] << ".cpp\n\n";

	// All other targets (.h wih .cpp files)
	for (int i = 1; i < files.size(); i++)
	{
		outFile << files[i] << ".o: " << files[i] << ".cpp " << files[i] << ".h\n";
		outFile << "\t$(CC) $(FLAGS) -c " << files[i] << ".cpp "
			 << "-o " << files[i] << ".o\n\n";
	}

	// Clean target
	outFile << "clean:\n";
	outFile << "\trm -f *.o " << output << ' ' << output << ".tar " << output
		 << ".scr\n";
	outFile << "\t@echo \"All clean!\"\n\n";

	// Tar target
	outFile << "tar:\n";
	outFile << "\ttar cf " << output << ".tar " << output << ".scr Makefile "
		 << files[0] << ".cpp ";

	for (int i = 1; i < files.size(); i++)
		outFile << files[i] << ".h " << files[i] << ".cpp ";
	outFile << endl;

	outFile.close();

	cout << "\n\nDone! Please move the file \"Makefile\" to your desired "
					"directory.\n\n";
	// Done

	return 0;
}
