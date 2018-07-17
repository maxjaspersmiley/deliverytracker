
#include <iostream>
#include <fstream>

using namespace std;

int main()
{
	ifstream inputFile;
	inputFile.open("citymap.txt");

//	ofstream outputFile;
//	outputFile.open("citymap.edit");


	int counter = 0;

	int address;
	int dist;
	int speed;
	int lastaddress = 0;
	

	char ch;

	while(inputFile >> address >> dist >> speed)
	{	
			

		cout 	<< "location " << counter
			<< " is connected to: " << address 
			<< " by a road length " << dist 
			<< " miles, with a speed limit of " << speed << endl;

		ch = inputFile.peek();
		if(ch == '\n')
		{
			cout << "#### end of connections for " << counter << " ####" << endl << endl;
			counter++;
		}

	}


	inputFile.close();








	return 0;
}
