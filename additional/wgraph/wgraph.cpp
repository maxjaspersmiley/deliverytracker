#include <iostream>
#include <fstream>

using namespace std;

struct edge
{
	int address;
	int distance;
	int speedlimit;
	
	edge * next;
};

struct vertex
{
	edge * head;
//	edge * tail;
};

void printVertex(vertex, int);

int main()
{
	vertex map[21];
	
	ifstream inputFile;
	inputFile.open("citymap.txt");


	int counter = 0;

	int address;
	int dist;
	int speed;
	int lastaddress = 0;

	char ch;

	edge * newedge = NULL;

	for(int i = 0; i < 21; i++)
	{
		map[i].head = NULL;
	}

	while(inputFile >> address >> dist >> speed)
	{
		newedge = NULL;
		if(map[counter].head != NULL)
		{
			newedge = map[counter].head;
		}

		map[counter].head = new edge;
		map[counter].head->address = address;	
		map[counter].head->distance = dist;
		map[counter].head->speedlimit = speed;
		
		map[counter].head->next = newedge;
	
		ch = inputFile.peek();
		if(ch == '\n')
		{
			counter++;
		}


	}

	inputFile.close();

	
	
	for(int i = 0; i < 21; i++)
	{
		printVertex(map[i], i);
	}

}

void printVertex(vertex myvert, int count)
{
	edge * myedge = myvert.head;
	do
	{
		cout 	<< "location " << count
			<< " is connected to: " << myedge->address
			<< " by a road length " << myedge->distance
			<< " miles, with a speed limit of " << myedge->speedlimit << endl;
		
		myedge = myedge->next;

	}
	while(myedge != NULL);

	cout << "#### end of connections for " << count << " ####" << endl << endl;
}

















