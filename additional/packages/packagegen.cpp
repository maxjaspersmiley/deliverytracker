#include <iostream>
#include <fstream>
#include <ctime>
#include <cstdlib>

using namespace std;

int main()
{

	const char * outname = "packages.txt";
	ofstream output;
	output.open(outname);

	srand(time(0));
	
	int type, destination, size, weight, numpackages, numdestinations;

	cout << "How many packages shall we generate? ";
	cin >> numpackages;

	cout << "How many destinations will there be? ";
	cin >> numdestinations; 



	for(int i = 0; i < numpackages; i++)
	{
		destination = (rand() % (numdestinations));

		size = (rand() % 31);
		if(size >= 10)
		{
			size = size / 10;
		}

		weight = (rand() % 500);
		if(weight >= 200)
		{
			weight = weight / 200;
		}		

		if(size <= 1 && weight <= 10)
		{
			type = (rand() % 3);
		}
		else
		{
			type = (rand() % 2) + 1;
		}

		output << type << ' ';
		output << destination << ' ';
		output << size << ' ';
		output << weight << endl;
	}

	cout << endl << endl << "file '" << outname << "' has been populated with " << numpackages << " randomly generated packages." << endl;
	cout << "Thank you for using Package Generator! Have a nice day." << endl << endl;

	output.close();

	return 0;
}






